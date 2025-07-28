# EE_bachelor_thesis (2024.03~2024.06)

&nbsp;

## 🧠 Robotic Arm Control Using Deep Learning-Based Electrooculogram


&nbsp;

## 🔗 출처 및 라이선스
1. **A Method of EOG Signal Processing to Detect the Direction of Eye Movements**  
   - Manuel Merino, Octavio Rivera, Isabel Gómez, Alberto Molina, Enrique Dorronzoro  
   - Electronic Technology Department, University of Seville, Spain  

2. **ArduinoTensorFlowLiteTutorials / GestureToEmoji**  
   - https://github.com/arduino/ArduinoTensorFlowLiteTutorials/tree/master/GestureToEmoji

3. **AUTODESK Instructables - 3D Printed Robot Arm by Beaconsfield**  
   - https://www.instructables.com/3D-Printed-Robot-Arm
     
&nbsp;

## 📑 목차

1. [📌 프로젝트 개요](#1--프로젝트-개요)  
2. [🔧 구성 요소](#2--구성-요소)  
3. [💻 사용 기술](#3--사용-기술)  
4. [🧭 동작 흐름 요약](#4--동작-흐름-요약)  
5. [💻 코드 실행 방법](#5--코드-실행-방법)  
6. [📷 시연 영상/이미지](#6--시연-영상--이미지)  
7. [🌟 기대 효과/ 한계점 및 개선점](#7--기대-효과)  

   
&nbsp;
## 1. 📌 프로젝트 개요

고령화 사회와 인적 자원의 한계로 인해 노년층을 돌보는 데 어려움이 있으며, 팔의 움직임이 불편한 사람들은 일상생활에서 기본적인 활동조차 어렵습니다.  
따라서 **극도로 운동 능력이 저하된 사람도 최소한의 자유로운 활동을 보장할 수 있는 보조기기의 필요성**이 커지고 있습니다.

이 프로젝트는 **EOG 센서를 이용한 안구 움직임 인식 기반 로봇팔 제어 시스템**을 개발하여,  
식사 상황에서 사용자가 팔을 사용하지 않고 **눈의 움직임만으로 원하는 음식을 집을 수 있도록 하는 것을 목표**로 합니다.

- EOG 센서를 착용하면 시선의 방향과 강도에 따른 신호값을 실시간으로 수집하고,  
- 아두이노로 데이터를 전송 후, 딥러닝 모델을 통해 시선 방향을 분류  
- 예측된 방향값을 기반으로 **3D 프린터로 제작한 로봇 팔을 움직여 음식 집기 동작 수행**

&nbsp;

### 🎯 기획 의도

- **노년층 및 거동 불편자의 식생활 자립**을 위한 사용자 친화적 인터페이스 개발  
- 손의 움직임 없이 **단순한 눈의 움직임(좌/우/깜빡임)** 만으로도 원하는 동작 수행  
- 예) 왼쪽/오른쪽 시선 → 로봇 이동, **크게 눈을 깜빡임** → 음식 집기

> 최근 EOG 연구는 센서 데이터 처리 및 시선 추적에 집중되어 있으며,  
> **하드웨어와 결합된 실시간 응용은 제한적**입니다.  
> 본 프로젝트는 **EOG 신호 처리 + 인공지능 학습 + 실제 로봇 제어**라는 전 과정을 수행함으로써 높은 의의를 가집니다.

&nbsp;

### 🏭 기존 기술의 활용과 협동로봇의 확장 가능성

- **EOG + Arduino + 딥러닝 모델**의 융합으로 저비용 고효율 시스템 구현  
- **TensorFlow Lite**를 활용하여 경량화된 모델을 실시간 임베디드 시스템에서 구동  
- **3D 프린팅 로봇 팔**을 직접 제작하여 개인 맞춤형 적용 가능

→ 향후 **협동 로봇(Cobot)** 으로 확장하여  
- 재활 의료, 장애 보조 장비,  
- 또는 **비접촉 인터페이스 기반의 스마트홈 제어 시스템** 등 다양한 응용 가능성 확보

&nbsp;
## 2. 🔧 구성 요소

| 구성 요소            | 설명                                                                 | 이미지 |
|---------------------|----------------------------------------------------------------------|--------|
| **Arduino Nano 33 BLE Sense** | EOG 센서로부터 신호를 받아 실시간으로 시선 방향을 분석하고, 딥러닝 모델을 통해 판단된 결과에 따라 로봇팔을 제어함. | <img width="300" src="https://github.com/user-attachments/assets/5a5c921e-9021-4990-8892-2aa33eaebafc" /> |
| **PSL-iEOG2 EOG 센서**        | 안구 전위(Electrooculogram)를 감지하여 눈의 좌우 움직임과 깜빡임 등을 아날로그 신호로 출력함.           | <img width="300" src="https://github.com/user-attachments/assets/dc2073be-53a0-4884-b0e6-b9ad2de862f3" /> |
| **서보 모터 (SG90 / MG995)** | 로봇팔 관절을 구동하여 시선 방향에 따라 원하는 위치로 움직임을 수행함. MG995는 힘이 필요한 부위, SG90은 가벼운 부위에 사용됨. | <img width="300" src="https://github.com/user-attachments/assets/97048b8f-518e-4930-895a-cad75dea3428" /> |
| **3D 프린터 로봇팔** | 실제 음식을 집을 수 있도록 설계된 로봇 팔 구조물. 3D 프린터로 출력하여 사용자 맞춤형 형태로 제작 가능.         | <img width="300" src="https://github.com/user-attachments/assets/2814adce-4669-40f8-b355-288e6d7c45f6" /> |

- PSL-iEOG2 : 168,960원
- arudino Nano 33 BLE : 59,900원
- TowerProM mg995 모터 4개 : 26000원
- SG-90 모터 2개 :２,800원
- AA*3 배터리팩 4개 : 4000원
- AA 배터리 5개 : 13500원
- 아두이노 우노 2개 :19800원
- 배터리 3구 홀더 2개 : 1980원
- breadboard 1개 : 800원
- arudino uno R3 : 26500원
- arudino nano : 29100원
- breadboard Jumper 18개 : 43200원

&nbsp;

## 3. 💻 사용 기술

| 기술 | 내용 |
|------|------|
| 💻 OS 및 환경 | Ubuntu 22.04, ROS2 Humble |
| 💬 사용 언어 | Python, DSR |
| 🔗 통신 미들웨어 | ROS2 (Publisher / Subscriber 기반 노드 통신) |
| 🧪 순응제어 | Doosan M0609 Force 센서를 활용한 충돌 감지 및 위치 파악 |
| 🧠 서브 제어 컨트롤러 | Raspberry Pi (로컬 ROS2 노드 실행 및 장치 제어) |
| 🎮 인터페이스 | 사용자 입력 기반 물품 선택 |
| 🖥 디스플레이/음성 | Raspberry Pi + LCD + 음성 출력 |

&nbsp;
## 4. 🧭 동작 흐름 요약

<img width="652" height="473" alt="image" src="https://github.com/user-attachments/assets/340626b4-d98d-4b9c-bfdc-103f4d0fc735" />

&nbsp;

### 📡 EOG 수집
EOG란 각막과 망막 간 전위를 측정 결과 발생하는 신호로 눈의 움직임을 기록할 때 주로 사용된다.  
피지오랩사의 PSL EOG 센서를 이용하여 안구전도를 측정하였고, 아두이노 나노와 연결하여 Arduino IDE 및 Serial SW를 통해 측정 결과를 확인하였다.

이번 논문에서는 눈의 좌우에 전극을 배치하여 horizontal한 EOG를 얻었다.  
전극은 총 3개로 양안의 좌우와 이마 중앙에 부착하여 전압차이를 각각 측정할 수 있다.

- PSL 센서는 2채널 신호를 제공 (아날로그, 디지털)  
- 이 중 아날로그 신호만 사용  
- 750V/V 증폭도  
- 60Hz notch filter 포함  
- 0.05Hz cutoff frequency의 high pass filter  
- 10Hz cutoff frequency의 low pass filter  
- 출력 전압: 0~3.3V

<img width="797" height="281" alt="image" src="https://github.com/user-attachments/assets/408c7b3e-a216-483f-af66-ad0f24a5c994" />

<img width="807" height="404" alt="image" src="https://github.com/user-attachments/assets/937b0241-c563-4d71-8d9b-f2b6f350d047" />

분석을 위해 먼저 데이터 전처리를 수행하였다.

- Sampling frequency를 125Hz로 downsampling  
- 평균 값 제거 및 scale 확대를 통해 데이터를 더 정확히 파악  
- 1초 간격으로 정면과 left (또는 right)를 바라봄  
- 2초 간격 (250 sample) 으로 EOG를 분리하여 확인

결과를 보면 왼쪽과 오른쪽을 바라봤을 때의 EOG 파형은 차이가 있었다.  
- 왼쪽 → 중앙에서 아래로 떨어지는 파형  
- 오른쪽 → 위로 튀는 파형  

전체 데이터 셋에서 확인해보면 아래와 같은 파형이다.

> 특히 현재 측정 중인 EOG는 안구 움직임의 변화를 측정하기 때문에  
> 왼쪽과 오른쪽 EOG 간의 데이터 절대값 크기는 큰 차이가 없었으며,  
> threshold로 단순 분류하기엔 한계가 있었다.

<img width="800" height="233" alt="image" src="https://github.com/user-attachments/assets/099fff83-1609-4978-b938-a644da3eaa8b" />

&nbsp;

### 🔀 기울기 기반 분석

처음 방향 변화가 일어난 순간에만 EOG 변화의 기울기가 다른 것을 확인하였다.  
따라서 **안구 움직임 변화 직후 5초간의 EOG 데이터를 수집하고, 미분값으로 데이터셋을 구성**하였다.

<img width="800" height="249" alt="image" src="https://github.com/user-attachments/assets/6ff94c7b-98b6-4777-b3ae-cfd5dbbab40b" />

- 번갈아가며 30도, 90도 시선 전환 실험  
- 수치적으로 큰 차이는 없음  
→ 왼쪽, 오른쪽, 가운데만 분류한 후 **횟수로 각도 조절**

&nbsp;

### 🤖 모델 제작

- 각 데이터셋을 `SAMPLES_PER_EOG` 값인 5개 샘플로 나눠 데이터프레임에 저장  
- 각각 1차원 배열로 변환 후 `inputs` 리스트에 저장 

<img width="700" height="159" alt="image" src="https://github.com/user-attachments/assets/cd734c30-e586-48d6-a6b2-b6d0f463d68a" />

- 해당 세그먼트가 나타내는 눈동자 움직임 유형: `left`, `right`, `center`  
- 이를 one-hot encoding하여 `outputs` 리스트에 저장

&nbsp;

### 🤖 모델 비교 및 선정

EOG 방향 분류를 위한 3가지 모델을 구현하고 성능 비교 후 최종 모델 선정

- CNN: 정확도 80.7%  
- SVM: 정확도 88.8%  
- **LSTM: 정확도 92.5% → 최종 선택**

<img width="700" height="300" alt="image" src="https://github.com/user-attachments/assets/e5efd2e9-1446-4b7b-b44f-40b92dc432a2" />

<img width="1059" height="598" alt="image" src="https://github.com/user-attachments/assets/974decef-c945-4a01-bc82-730f28b3d2e4" />

&nbsp;

### 🛠️ 로봇팔 3D 프린팅 및 조립

- 복잡하고 정밀한 작업을 수행 가능한 6 DOF 로봇팔을 설계  
- 3D 모델링 진행 후 부품 제작 및 조립  
- 모터 구성:  
  - MG995 (기저 회전, 어깨 2개, 팔꿈치)  
  - SG90 (팔목, 집게)

<img width="800" height="253" alt="image" src="https://github.com/user-attachments/assets/b0077c95-b36c-4cac-a398-0931d86e590d" />

&nbsp;

### 🔌 회로 구성

- 각 모터 전선을 연장 후 Arduino 보드 핀 번호에 맞게 연결  
- 모터에 강한 힘을 주기 위해 5V 파워 서플라이를 별도 연결  
- 전력 손실 최소화를 위해 짧은 점프선 사용

&nbsp;

### 💻 Arduino 코드 구성

- 사용 보드: **Arduino Nano 33 BLE Sense**  
- Arduino 코드로 서보모터 제어 → 로봇팔 동작 구현
- 각 모터의 핀과 각도 제어를 통해 **정확한 집기 동작** 구현

<img width="1119" height="759" alt="image" src="https://github.com/user-attachments/assets/0052be4e-ef41-47a7-84c9-b2604e01437f" />

<img width="1124" height="723" alt="image" src="https://github.com/user-attachments/assets/58e24a3b-5bac-46b5-af82-9e61803bb4fe" />

&nbsp;

### 🔁 방향 전환 로직

- EOG 센서를 이용해 방향 전환 감지  
- 상태 머신 설계(State Machine)로 방향에 따라 로봇팔 동작 분기

<img width="1124" height="629" alt="image" src="https://github.com/user-attachments/assets/6f8ef34f-51cc-4cb8-92f0-d392a9d9a9fc" />

<img width="440" height="158" alt="image" src="https://github.com/user-attachments/assets/58844b15-6e3e-4815-a592-17cf558783b1" />

<img width="883" height="399" alt="image" src="https://github.com/user-attachments/assets/1d651cbf-0edd-45bf-aee6-c6f938ea0c28" />

&nbsp;

## ✅ 결과

<img width="857" height="341" alt="image" src="https://github.com/user-attachments/assets/3a3af50d-4ca5-4de7-8538-c315d31d9a54" />

- 사용자의 눈 움직임만으로 로봇팔이 정확한 방향 전환 및 집기 동작 성공  
- LSTM 기반 EOG 분류 모델과 로봇팔 동작 시스템의 실시간 연동 가능성 확인

&nbsp;
## 5. 💻 코드 실행 방법

### 🤖 Robot Control Node
- 코드: [`robot_control_node.py`](./rokey_project/rokey_project/robot_control_node.py)

```bash
ros2 run rokey_project robot_control_node
```

&nbsp;



## 6. 📷 시연 영상 / 이미지
> https://youtu.be/bbBvETzXTgY

&nbsp;
## 7. 🌟 기대 효과
- 기대효과
eog 센서는 빠른 반응 속도를 제공해 사용자의 의도를 즉시 반영할 수 있다. 이를 통해 로봇팔의 실
시간 제어를 가능하게 하여 효율성이 높아질 수 있다. 또한 피부에 부착하는 방식이므로, 수술이나 복
잡한 설치 과정 없이 몸이 불편한 사용자가 편하게 사용이 가능하여 접근성과 안전성이 높다. 이를 활
용하여 산업, 의료, 서비스 등 여러 분야에서 응용 범위를 확장시켜 발전시킬 수 있다.
- 활용방안
신체 일부가 불편한 사람들을 위한 보조기기로 활용될 수 있다. 또한 eog 센서를 이용한 로봇팔 제어
는 재활 치료에서 사용자의 자율성을 증진시켜 환자의 회복을 돕는 데 큰 도움을 줄 수도 있다. 이외
에도 정밀 작업이 필요한 산업 분야나 카페나 레스토랑과 같이 음료나 음식의 서빙이 필요한 서비스
분야에도 적극 활용될 수 있다.
### 결론 및 제언
eog 센서를 이용한 로봇팔 제어 기술은 생체 신호를 이용한 정밀하고 신속한 제어를 가능하게 한다.
이 기술은 비침습적인 인터페이스를 통해 사용자의 편의성과 안전성을 보장하며, 다양한 환경과 작업
조건에서 효율적으로 적용될 수 있다. 여러 분야에서의 활용 가능성을 고려할 때, eog 센서를 이용한
로봇팔 제어 기술은 인간의 생활을 더욱 풍요롭게 하고, 새로운 혁신을 이끌어 낼 수 있는 잠재력을
가지고 있다고 본다. 그러므로 지속적인 연구와 개발, 사용자 중심의 접근, 윤리적 고려와 사회적 수용
성을 바탕으로 이 기술이 더욱 발전하고, 우리의 삶에 긍정적인 영향을 미칠 수 있기를 기대한다


&nbsp;
## 🙌 팀원

-윤하연, 정서윤, 안병호 


