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

## 🔧 구성 요소

| 구성 요소            | 설명                                                                 | 이미지 |
|---------------------|----------------------------------------------------------------------|--------|
| **Arduino Nano 33 BLE Sense** | EOG 센서로부터 신호를 받아 실시간으로 시선 방향을 분석하고, 딥러닝 모델을 통해 판단된 결과에 따라 로봇팔을 제어함. | <img width="120" src="https://github.com/user-attachments/assets/5a5c921e-9021-4990-8892-2aa33eaebafc" /> |
| **EOG 센서**        | 안구 전위(Electrooculogram)를 감지하여 눈의 좌우 움직임과 깜빡임 등을 아날로그 신호로 출력함.           | ![eog 사진](https://github.com/user-attachments/assets/dc2073be-53a0-4884-b0e6-b9ad2de862f3) |
| **서보 모터 (SG90 / MG995)** | 로봇팔 관절을 구동하여 시선 방향에 따라 원하는 위치로 움직임을 수행함. MG995는 힘이 필요한 부위, SG90은 가벼운 부위에 사용됨. | ![모터사진](https://github.com/user-attachments/assets/97048b8f-518e-4930-895a-cad75dea3428) |
| **3D 프린터 로봇팔** | 실제 음식을 집을 수 있도록 설계된 로봇 팔 구조물. 3D 프린터로 출력하여 사용자 맞춤형 형태로 제작 가능.         | <img width="140" src="https://github.com/user-attachments/assets/2814adce-4669-40f8-b355-288e6d7c45f6" /> |



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
<img width="600" height="224" alt="image" src="https://github.com/user-attachments/assets/f9b3e453-4a83-46d6-85bd-8abab347f9d9" />
<img width="600" height="1463" alt="image" src="https://github.com/user-attachments/assets/059756fc-f98b-4823-a8c3-b05fa19cbf83" />

&nbsp;
### 🏠 퇴근 모드

0. **사용자 아이템 리스트**  
   - 카드키, 껌, 지갑, 스낵, 텀블러

1. **홈 위치 대기**  
   - Force 센서를 활용해 충돌 감지 상태에서 대기

2. **수납 알고리즘 시작**  
   - y축 방향 외력 감지 (Check Force Condition) → 수납 알고리즘 진입  
   - 💬 음성 출력: `"Good night! Have a sweet dream"`  
   - 📺 LCD 출력: `good night!`

3. **인사 동작 (Good night)**  
   - `Move_periodic` 동작으로 인사 수행  
   - 💬 음성 출력: `"Good night!"`  
   - 📺 LCD 출력: `"Good night!"`

4. **사용자 입력**  
   - 원하는 물체 및 선반 위치 입력  
   - 예: `텀블러 1`

5. **물체 탐색**  
   - ㄹ자 구조로 반복 탐색 수행  
     - Movel 명령으로 x축 400mm, y축 50mm 탐색  
   - 📺 LCD 출력: `"Searching"` Gage 애니메이션 표시

6. **물체 분류 및 Grip 동작**  
   - 비동기 탐색 중 `Get tool force`로 외력 감지 → 물체 존재 확인  
   - 📺 LCD 출력: `"grabbed object!: {Detected name}"`  
   - 💬 음성 출력: `{Detected name}`  
   - 순응제어로 z축 위치 파악 → `height_dict`와 비교하여 분류  
   - `Release` → `Grip` 동작으로 물체 집기

7. **입력 위치에 물품 수납**  
   - **비어있는 경우**: 원래 위치 (`placed_list`)에 수납  
   - **이미 물건이 있는 경우**:  
     - 예: `stacked = [1, 0, 0, 0]` → `stacked = [2, 0, 0, 0]`  
     - x축으로 떨어진 지점에 수납  
   - 📺 LCD 출력: `"Placed object: {Detected name}"`  
   - 💬 음성 출력: `{Detected name}`

8. **그리퍼 홈 위치 복귀**  
   - 수납 완료 후, 그리퍼가 홈 위치로 이동하여 대기  
   - 📺 LCD 출력: `"Request complete"`  
   - 💬 음성 출력: `"Request complete"`

&nbsp;
### 🚪 출근 모드
0. **홈 위치 대기**  
   - Force 센서를 활용해 충돌 감지 상태에서 대기

1. **꺼내기 알고리즘 시작**  
   - x축 방향 외력 감지 (Check Force Condition) → 꺼내기 알고리즘 진입  
   - 💬 음성 출력: `"Have a nice day!"`  
   - 📺 LCD 출력: `"Hello, Have a nice day!"`

2. **인사 동작 (Hello)**  
   - `Move_periodic` 동작으로 인사 수행  
   - 💬 음성 출력: `"Hello!"`  
   - 📺 LCD 출력: `"Hello!"`

3. **사용자 입력**  
   - 원하는 물체 및 선반 위치 입력  
   - 예: `텀블러 1`

4. **물품 위치 비교 및 꺼내기**  
   - **입력값과 위치가 일치하는 경우** → 해당 위치에서 물건 꺼냄  
     - 📺 LCD 출력: `{Detected name} out`  
     - 💬 음성 출력: `{Detected name}`  
   - **불일치하는 경우** → 동작 수행하지 않음

5. **꺼낸 물품 배치**  
   - 최대 5개까지 꺼낼 수 있음  
   - 입력된 순서대로, 홈 위치에서 일정 간격으로 떨어진 위치에 배치

6. **그리퍼 홈 위치 복귀**  
   - 꺼내기 완료 후, 그리퍼가 홈 위치로 복귀  
   - 📺 LCD 출력: `"Request complete"`  
   - 💬 음성 출력: `"Request complete"`

&nbsp;
## 5. 💻 코드 실행 방법

### 🤖 Robot Control Node
- 코드: [`robot_control_node.py`](./rokey_project/rokey_project/robot_control_node.py)

```bash
ros2 run rokey_project robot_control_node
```
### 🍓 Raspberry Pi Node
- 코드: [`feedback_node.py`](./rokey_project/rokey_project/feedback_node.py)

```bash
ros2 run rokey_project feedback_node
```
&nbsp;
## 6. 📷 시연 영상 / 이미지
> https://youtu.be/bbBvETzXTgY

> <img width="600" height="415" alt="image" src="https://github.com/user-attachments/assets/52fde78e-1d48-4131-9ba5-a52d8baa4287" />

> <img width="600" height="415" alt="image" src="https://github.com/user-attachments/assets/24839a30-8b8b-4170-aeda-596b4a016ea2" />

> <img width="600" height="392" alt="image" src="https://github.com/user-attachments/assets/a3af83a5-ea75-4e62-b817-4eddd1cb01de" />

> <img width="300" height="300" alt="image" src="https://github.com/user-attachments/assets/bfb44ccb-1988-4563-abb9-64399405e04d" />


&nbsp;
## 7. 🌟 기대 효과

- 일상생활에 협동로봇 도입 가능성 증진
- 출퇴근 시간의 불편함 해소
- 다양한 물품 및 센서로의 확장성 기대

### ⚠️ 한계점 및 개선점

- 그리퍼의 중량, 가속도/속도에 따른 force 조절 미흡 → 물체 밀림 발생
- 선반 높이 제한 → 워크스페이스 조정 필요

&nbsp;
## 🙌 팀원

- 백홍하,정서윤,정민섭,서형원


