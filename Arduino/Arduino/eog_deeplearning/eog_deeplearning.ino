#include <Arduino.h>
#include <Servo.h>
#include <mbed.h>
#include <TensorFlowLite.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/tflite_bridge/micro_error_reporter.h"
#include "Eog_model1.h"

const int numSamples = 5;
float eogData[numSamples];
int samplesRead = numSamples;
int currentIndex = 0;
bool modelInvoked = false;
float maxProbability = 0.0;
int maxIndex = 0;
// global variables used for TensorFlow Lite (Micro)
tflite::MicroErrorReporter tflErrorReporter;

// pull in all the TFLM ops, you can remove this line and
// only pull in the TFLM ops you need, if would like to reduce
// the compiled size of the sketch.
tflite::AllOpsResolver tflOpsResolver;

const tflite::Model* tflModel = nullptr;
tflite::MicroInterpreter* tflInterpreter = nullptr;
TfLiteTensor* tflInputTensor = nullptr;
TfLiteTensor* tflOutputTensor = nullptr;

// Create a static memory buffer for TFLM, the size may need to
// be adjusted based on the model you are using
constexpr int tensorArenaSize = 8 * 1024;
byte tensorArena[tensorArenaSize] __attribute__((aligned(16)));
unsigned long lastTime = 0;  // 마지막 측정 시간
float lastSample = 0;  // 마지막에 측정된 샘플
int analogPin0 = A0;
float previousValue = 0;
float derivative = 0;

// array to map gesture index to a name
const char* GESTURES[] = {
  "left", "right","center"
};

#define NUM_GESTURES (sizeof(GESTURES) / sizeof(GESTURES[0]))

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // get the TFL representation of the model byte array
  tflModel = tflite::GetModel(model);
  if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema mismatch!");
    while (1);
  }

  // Create an interpreter to run the model
  tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensorArena, tensorArenaSize);

  // Allocate memory for the model's input and output tensors
  tflInterpreter->AllocateTensors();

  // Get pointers for the model's input and output tensors
  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);
}

void loop() {
  unsigned long currentTime = millis();
  int reading = analogRead(analogPin0);
  float currentValue = (float)reading / 1023 * 5;

  if (currentTime - lastTime >= 1000) {
    lastTime = currentTime;
    float derivative = (currentValue * 10000 - lastSample * 10000) / 500.0;
    lastSample = currentValue;

   if (currentIndex < numSamples) {
      eogData[currentIndex] = derivative;
      currentIndex++;
    } else {
      // 배열이 이미 채워진 경우, 가장 오래된 데이터 제거 후 새 데이터 추가
      for (int i = 1; i < numSamples; i++) {
        eogData[i - 1] = eogData[i];
        Serial.println(eogData[i-1]);
      }
      eogData[numSamples - 1] = derivative;  // 새 데이터를 배열 끝에 저장
    }

    Serial.print("Derivative: ");
    Serial.println(derivative);
    
    if (currentIndex ==numSamples) {
      modelInvoked = false;  // 모델이 다시 실행될 준비가 되었음을 표시
    }
  }

  if (currentIndex==numSamples && !modelInvoked) {
    for (int i = 0; i < numSamples; i++) {
      tflInputTensor->data.f[i] = eogData[i];
    }

    TfLiteStatus invokeStatus = tflInterpreter->Invoke();
    if (invokeStatus != kTfLiteOk) {
      Serial.println("Invoke failed!");
      while (1);
      return;
    }

    for (int i = 0; i < NUM_GESTURES; i++) {
      Serial.print(GESTURES[i]);
      Serial.print(": ");
      Serial.println(tflOutputTensor->data.f[i], 6);
    
    if (tflOutputTensor->data.f[i] > maxProbability) {
        maxProbability = tflOutputTensor->data.f[i];
        maxIndex = i; // left ,right, ceter와 같은 상태는 GESTURES[maxIndex]로 하면 됌 
    }
    }
    Serial.println(GESTURES[maxIndex]);

    modelInvoked = true;  // 모델이 이미 실행되었음을 표시
  }
}
