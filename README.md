# KING_OF_OMOK
오목의 킹이 되겟어

</br>

## 프로젝트 개요
- 오목 게임을 Cpp 콘솔 프로그램으로 구현하기
- 객체지향적으로 구현하자 !
- 사용자 먼저 시작하므로 별다른 룰 없이 먼저 연속적인 5개의 돌을 놓는 쪽이 이긴다.

![image](https://user-images.githubusercontent.com/49704910/157182005-cd33d028-6ebe-40aa-8dc6-27028cfd548e.png)


## 클래스 개요
|No.|클래스|내용|
|-|-|-|
|1|User|게임 플레이어 클래스|
|2|Aset|오목 한판에 대한 정보를 가지는 클래스|
|3|GameProcessor|게임 플레이를 위한 클래스|
|4|LeeSedol|컴퓨터와 대결을 위한 클래스|
|5|StartPage|게임 시작, 끝 화면|
|6|Core|콘솔 관련 기능 클래스|

</br>

## 1. class User
프로그램 실행시 메인문에서 유저 객체를 생성하여 게임을 시작한다.
생성자에서 멤버 변수로 다른 클래스들을 나타내는 포인터(ptrAset, ptrGP, ptrLSD)를 정의하여 이를 통해 게임을 플레이한다.

### 멤버변수
|타입|변수명|내용|
|-|-|-|
|_Aset*|ptrAset|Aset객체는 게임 한판마다 생성되고 소멸됨|
|_GameProcessor*|ptrGP|static으로 이미 생성된 객체를 가르킴|
|_LeeSedol*|ptrLSD|static으로 이미 생성된 객체를 가르킴|

</br>

## 2. class Aset
- 게임 한판에 대한 정보를 배열로 가지는 클래스.
- 게임 한판이 끝나면 소멸된다.
- private으로 가지고 있는 멤버변수 Board를 User에게 공유해야 하므로 User를 friend 선언하여 사용한다.

### 멤버변수
|타입|변수명|내용|
|-|-|-|
|int|Board[SIZE][SIZE]|현재 게임에 대한 정보를 가지고 있는 정수형 배열|


</br>

## 3. GameProcessor
- 게임 진행을 위한 클래스.
- 매 게임 같은 동작을 수행하므로 Static으로 선언하여 사용한다.
- Aset의 오목 판 정보(Board)에 포인터로 직접 접근하여 게임을 진행한다.

### 멤버변수
|타입|변수명|내용|
|-|-|-|
|int*|(* Board)[SIZE]|Aset 클래스의 멤버변수 Board에 접근하기 위한 포인터 (2차원 배열 접근)|

### 멤버함수
|타입|함수명|내용|
|-|-|-|
|void|setBoard|GameProcessor 클래스의 포인터 (* Board)[SIZE]에 Aset 클래스의 멤버변수 Board를 저장하는 함수|
|void|putStone|바둑돌을 위치시키는 함수|
|void|drawBoard|바둑판을 그리는 함수|
|int|isEnd|연속된 5개의 돌이 있는지 확인하여 게임이 끝났는지 판단하는 함수|
|void|moveCursor|키보드를 입력받는 함수|
|bool|showMessage|게임 한판 종료 후 메세지를 출력하는 함수|

</br>

## 3. LeeSedol
- 컴퓨터와 대결하는 클래스
- 매 게임 같은 동작을 수행하므로 Static으로 선언하여 사용한다.
- Aset의 오목 판 정보(Board)에 포인터로 직접 접근하여 게임을 진행한다.
게임 초기에는 바둑돌이 놓일 때마다 가중치를 계산하여 다음에 놓일 최적의 위치를 계산한다. (참고 :https://ku-hug.tistory.com/2) 다만 게임이 진행 될 수록 실제 승리할 수 있는 수와 가중치를 통해 계산한 수가 달라지게 되므로, 바둑돌 위치를 통한 가중치 계산 외에도 실제 게임에 영향을 주는 경우(세개 이상 돌이 연속된 경우)를 따로 탐색하여 가중치를 부여한다. __게임 레벨이 높아질수록 더 많은 경우의 수를 탐색__ 하여 난이도를 어렵게 하였다.

### 멤버변수
|타입|변수명|내용|
|-|-|-|
|int*|(* Board)[SIZE]|Aset 클래스의 멤버변수 Board에 접근하기 위한 포인터 (2차원 배열 접근)|

### 멤버함수
|타입|함수명|내용|
|-|-|-|
|void|setBoard|LeeSedol|클래스의 포인터 (* Board)[SIZE]에 Aset 클래스의 멤버변수 Board를 저장하는 함수|
|pair<int,int>|computerTurn|바둑돌을 두기 위한 최적의 위치를 찾는 함수</br> 바둑돌 위치를 반환하고, 이를 그리는것은 GameProcessor 객체가 수행|
|void|gameForLevel_1|가중치를 계산하기 위한 함수(레벨1)|
|void|gameForLevel_2|가중치를 계산하기 위한 함수(레벨2)|
|pair<int, int>|gameForLevel_3|가중치를 계산하기 위한 함수(레벨3)|
