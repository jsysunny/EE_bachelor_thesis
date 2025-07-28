#include <Arduino.h>
#include <Servo.h>
#include <mbed.h>
#include <TensorFlowLite.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/tflite_bridge/micro_error_reporter.h"
#include "Eog_model1.h"

Servo sg90_1;   // finger
Servo sg90_2;   // wrist
Servo mg995_1;  // arm1
Servo mg995_2;  // arm2 left
Servo mg995_3;  // arm2 right
Servo mg995_4;  // turn

const int servoPin_1 = D2;  // sg90_1
const int servoPin_2 = D3;  // sg90_2
const int servoPin_3 = D4;  // mg995_1
const int servoPin_4 = D5;   // mg995_2
const int servoPin_5 = D6;   // mg995_3
const int servoPin_6 = D9;   // mg995_4

// positions of motors
int pos_sg90_1; 
int pos_sg90_2;   
int pos_mg995_1;  
int pos_mg995_2;  
int pos_mg995_3;  
int pos_mg995_4 = 80; 
int reg_pos_mg995_4;

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
unsigned long lastTime_2 = 0;
float lastSample = 0;  // 마지막에 측정된 샘플
int analogPin0 = A0;
float previousValue = 0;
float derivative = 0;

enum Gesture {
  LEFT,
  RIGHT,
  CENTER,
  NONE  // 초기 상태 또는 알 수 없는 상태
};

// array to map gesture index to a name
const char* GESTURES[] = {
  "left", "right","center"
};

#define NUM_GESTURES (sizeof(GESTURES) / sizeof(GESTURES[0]))
Gesture gestureFromString(const char* gestureStr) {
  for (int i = 0; i < NUM_GESTURES; i++) {
    if (strcmp(gestureStr, GESTURES[i]) == 0) {
      return static_cast<Gesture>(i);
    }
  }
  return NONE;  // 일치하는 문자열이 없는 경우
}



void setup() {
  Serial.begin(9600);
  while (!Serial);
  sg90_1.attach(servoPin_1, 600, 2100);
  sg90_2.attach(servoPin_2, 600, 2100);
  mg995_1.attach(servoPin_3, 600, 2100);
  mg995_2.attach(servoPin_4, 600, 2100);
  mg995_3.attach(servoPin_5, 600, 2100);
  mg995_4.attach(servoPin_6, 600, 2100);
  


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
     if (derivative > 35 || derivative <-35)
    {
      Serial.println("operate");
       // arm2 down
    for(pos_mg995_2 = 90, pos_mg995_3 = 10; pos_mg995_2 >= 40 && pos_mg995_3 <= 60; pos_mg995_2 -= 1, pos_mg995_3 += 1)
    {
      mg995_2.write(pos_mg995_2);
      mg995_3.write(pos_mg995_3);
      delay(20);
    }
    delay(500);

    // arm1 down
    for(pos_mg995_1 = 80; pos_mg995_1 <= 180; pos_mg995_1 += 1)
    {
      mg995_1.write(pos_mg995_1);
      delay(20);
    }
    delay(500);
/*
    // wrist down
    for(pos_sg90_2 = 0; pos_sg90_2 <= 100; pos_sg90_2 += 1)
    {
      sg90_2.write(pos_sg90_2);
      delay(20);
    }
    delay(500);
*/
    // finger grip
    for(pos_sg90_1 = 110; pos_sg90_1 >= 0; pos_sg90_1 -= 1)
    {
      sg90_1.write(pos_sg90_1);
      delay(20);
    }
    delay(500);
/*
    // wrist up
    for(pos_sg90_2 = 100; pos_sg90_2 >= 0; pos_sg90_2 -= 1)
    {
      sg90_2.write(pos_sg90_2);
      delay(20);
    }
    delay(500);
*/
    // arm1 up
    for(pos_mg995_1 = 180; pos_mg995_1 >= 80; pos_mg995_1 -= 1)
    {
      mg995_1.write(pos_mg995_1);
      delay(20);
    }
    delay(500);
  
    // arm2 up
    for(pos_mg995_2 = 40, pos_mg995_3 = 60; pos_mg995_2 <= 90 && pos_mg995_3 >= 10; pos_mg995_2 += 1, pos_mg995_3 -= 1)
    {
      mg995_2.write(pos_mg995_2);
      mg995_3.write(pos_mg995_3);
      delay(20);
    }
    delay(500);

    // finger open
    for(pos_sg90_1 = 0; pos_sg90_1 <= 110; pos_sg90_1 += 1)
    {
      sg90_1.write(pos_sg90_1);
      delay(20);
    }
    delay(500);

    }
    eogData[currentIndex] = derivative;
    lastSample = currentValue;

    Serial.print("Derivative: ");
    Serial.println(derivative);

    currentIndex = (currentIndex + 1) % numSamples;

    if (currentIndex == 0) {
      modelInvoked = false;  // 모델이 다시 실행될 준비가 되었음을 표시
    }
  }

  if (currentIndex == 0 && !modelInvoked) {
    maxProbability=0.0;
    maxIndex=0;
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
    //Serial.println(GESTURES[maxIndex]);
    
    Gesture currentGesture = gestureFromString(GESTURES[maxIndex]);
    switch (currentGesture)
  {
    case RIGHT: {
          Serial.println("Right");
          for (reg_pos_mg995_4 = pos_mg995_4 - 40; pos_mg995_4 >= reg_pos_mg995_4; pos_mg995_4 -= 1)
          {
            mg995_4.write(pos_mg995_4);
            delay(15);
          }
          break;
    }
    case LEFT:{
          Serial.println("Left");
          for (reg_pos_mg995_4 = pos_mg995_4 + 40; pos_mg995_4 <= reg_pos_mg995_4; pos_mg995_4 += 1)
          {
            mg995_4.write(pos_mg995_4);
            delay(15);
          }
          break;
    }

    case CENTER:
    {
            Serial.println("Center");
          break;
    } //center 

    } // gesture 분류 ( right, left, center)
   
        modelInvoked = true;  // 모델이 이미 실행되었음을 표시
  } // 모델 입력 괄호 (5개의 eog 데이터 받은 후)
  
} // 전체 loop

  

