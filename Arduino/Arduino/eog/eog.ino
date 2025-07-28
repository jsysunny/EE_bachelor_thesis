#include <TimerOne.h>
#include <Servo.h>

Servo mg995_2;
Servo mg995_3;

const int servoPin_4 = 9;
const int servoPin_5 = 8;
int pos_mg995_2;
int pos_mg995_3;

unsigned long lastTime = 0; 
float previousValue=0;
float lastSample = 0;  // 마지막에 측정된 샘플
int analogPin0 = 0;
float derivative1, derivative2;

enum State { right, left, center, operate };
State state = center;
State nstate;

void setup() 
{
  Serial.begin(9600);
  Timer1.initialize(50000); // 50,000us (50ms)
  //Timer1.attachInterrupt(AnalogAD);
  Timer1.start();

  mg995_2.attach(servoPin_4, 600, 2100);
  mg995_3.attach(servoPin_5, 600, 2100);
}

void loop() 
{
  int reading0 = analogRead(analogPin0);
  float currentValue = (float)reading0 / 1023 * 5;
  unsigned long currentTime = millis();  // 현재 시간
if(currentTime>1000)
{  
  if (currentTime - lastTime >= 1000) 
  {  // 1초가 지났는지 확인
      previousValue = lastSample;  // 1초 전의 값은 마지막 측정된 값으로 설정
      lastSample = currentValue;  // 현재 값 저장
     lastTime = currentTime;  // 마지막 측정 시간 업데이트

      derivative1=derivative2;
      // 미분 계산: e'(t) = (e(t) - e(t-n)) / n
      float derivative = (currentValue*10000 - previousValue*10000) / 500.0;
     derivative2=derivative;
  }
}

  switch (state)
  {
   case right:
    Serial.println("Right");
    for (pos_mg995_3 = 0; pos_mg995_3 <= 180; pos_mg995_3 += 1) 
    {
      mg995_3.write(pos_mg995_3);
      delay(15);
    }
    for (pos_mg995_3 = 180; pos_mg995_3 >= 0; pos_mg995_3 -= 1) 
    {
      mg995_3.write(pos_mg995_3);
      delay(15);
    }
    delay(1000);
    state = operate;
    break;
  
  case left:
    Serial.println("Left");
    for (pos_mg995_2 = 0; pos_mg995_2 <= 180; pos_mg995_2 += 1) 
    {
      mg995_2.write(pos_mg995_2);
      delay(15);
    }
    for (pos_mg995_2 = 180; pos_mg995_2 >= 0; pos_mg995_2 -= 1) 
    {
      mg995_2.write(pos_mg995_2);
      delay(15);
    }
    delay(1000);
    state = operate;
    break;  
  
  case operate:
   Serial.println("Operate");  // 작동 확인용 시리얼 프린트
    for (pos_mg995_2 = 0, pos_mg995_3 = 0; pos_mg995_2 <= 180 && pos_mg995_3 <= 180; pos_mg995_2 += 1, pos_mg995_3 += 1) 
    {
      mg995_2.write(pos_mg995_2);
      mg995_3.write(pos_mg995_3);
      delay(15);
    }
    delay(1000);
    state = center;
    break;  
  
  case center:
    Serial.println("Center");
  // 미분값이 임계치를 넘는지 확인
  if(derivative1 > 10 || derivative1 < -10)
    nstate = center;
  else if (derivative1 > 2.5 && derivative2 < -2.5)
    nstate = right;
  else if (derivative1 < -2.5 && derivative2 > 2.5)
    nstate = left;
  else
    nstate = center;

    state = nstate;
    delay(1000);
  break;
  }
}