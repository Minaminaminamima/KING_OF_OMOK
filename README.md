# KING_OF_OMOK
오목의 킹이 되겟어

</br>

## 프로젝트 개요
- 오목 게임을 Cpp 콘솔 프로그램으로 만들기
- 객체지향적으로 구현하자 !
- 별도의 룰 없이 먼저 연속적인 5개의 돌을 놓는 쪽이 이긴다.

![image](https://user-images.githubusercontent.com/49704910/157182005-cd33d028-6ebe-40aa-8dc6-27028cfd548e.png)


## 클래스 개요
- 클래스 네이밍 규칙은 앞자리에 (_)기호를 붙인다.

|No.|클래스|내용|
|-|-|-|
|1|_Aset|오목 한 게임에 대한 정보를 가지는 클래스|
|2|_GameProcessor|게임 플레이를 위한 클래스|
|3|_LeeSedol|컴퓨터와 대결을 위한 클래스|
|4|_TCPmode|다른 사용자와 대결하기 위한 클래스|
|5|_StartPage|게임 시작, 끝 화면을 보여주기 위한 클래스|
|6|_Core|콘솔 관련 기능 클래스|
|7|_User|게임 플레이어가 게임을 하기 위한 클래스를 모아놓은 클래스|
|8|_CommunicationMode|TCP/IP 통신 Server, Client 를 구현하기 위한 parents 클래스|
|9|_usrForServer|CommunicationMode를 상속받아 Server로 구현된 클래스|
|10|_usrForClient|CommunicationMode를 상속받아 Client로 구현된 클래스|

</br>

## 메인문 Flowchart

![image](https://user-images.githubusercontent.com/49704910/158346761-2d245828-1809-48d8-9966-c8533a31904f.png)


- __게임 시작__ : StartPage의 객체를 통해 시작 페이지를 출력한다. 시작 페이지에서 게임 모드(컴퓨터와 대결, 다른 유저와 대결)을 선택할 수 있다.
- __게임진행__
  - (1) 컴퓨터 모드 : 컴퓨터와 대결할 수 있는 LeeSedol 객체를 포함하는 User객체를 생성한다. 
  - (2) 유저와 대결(Server) : 다른 유저와 대결할 수 있도록 세션을 생성하는 usrForServer 객체를 생성한다. 서버 생성 후 클라이언트가 입장할 수 있다.
  - (3) 유저와 대결(Client) : 다른 유저와 대결할 수 있도록 세션을 생성하는 usrForClient 객체를 생성한다.  
- __게임 종료__ : 게임이 끝난 후 retrun되는 값(true, false)을 인자로 받아 엔딩 페이지를 다르게 출력한다(win, lose). 종료 후 다시 게임 시작 페이지로 돌아간다.



</br>

## 1. class Aset
- 게임 한판에 대한 정보를 배열로 가지는 클래스.
- 게임 시작시 생성되고, 끝나면 소멸된다.
- 게임의 주체인 User, CommunicationMode 클래스가 Private 속성인 Board에 접근할 수 있도록 friend class로 선언된다.

### 멤버변수
|타입|변수명|내용|
|-|-|-|
|int|Board[SIZE][SIZE]| 현재 게임에 대한 정보를 가지고 있는 2차원 배열|
|friend class|User|private property인 Board에 접근할 수 있도록 friend 선언|
|friend class|CommunicationMode|private property인 Board에 접근할 수 있도록 friend 선언|


</br>

## 2. class User
- 컴퓨터 모드로 게임시 생성되는 객체
- 다음 객체들을 참조하여 게임을 진행한다.
  - _Aset : 현재 게임을 위한 오목 판 
  - _GameProcessor : 게임 진행 동작 수행 (돌 그리기, 게임 종료 판정 등)
  - _LeeSedol : 컴퓨터와 대결모드 


### Class diagram

![image](https://user-images.githubusercontent.com/49704910/158114199-b04666f6-1a7c-465a-a6cc-ff956556b48e.png)

### 멤버변수
|타입|변수명|내용|
|-|-|-|
|_Aset*|ptrAset|Aset객체는 게임 한판마다 생성되고 소멸됨|
|_GameProcessor*|ptrGP|static _GameProcessor 객체 주소를 저장하여 사용|
|_LeeSedol*|ptrLSD|static _LeeSedol 객체 주소를 저장하여 사용|


</br>

## 3. class GameProcessor
- 게임 진행을 위한 클래스
- static으로 선언하여 싱글톤, 즉 하나의 객체만 생성하여 사용한다.
- _Aset 객체의 오목 판 정보(Board)에 포인터로 접근하여 게임을 진행한다.

### Class diagram
![image](https://user-images.githubusercontent.com/49704910/158114319-b6fed1f3-dea5-4bd7-99f6-4889e4a8ac3f.png)


### 멤버변수
|타입|변수명|내용|
|-|-|-|
|int|(* Board)[SIZE]|Aset 클래스의 멤버변수 Board에 접근하기 위한 포인터 (2차원 배열 접근)|

### 멤버함수
|타입|함수명|내용|
|-|-|-|
|void|setBoard|멤버변수 (* Board)[SIZE]에 Aset 클래스의 멤버변수 Board를 저장하는 함수|
|void|putStone|바둑돌을 위치시키는 함수|
|void|drawBoard|바둑판을 그리는 함수|
|int|isEnd|연속된 5개의 돌이 있는지 확인하여 게임이 끝났는지 판단하는 함수|
|void|moveCursor|키보드를 입력받는 함수|
|bool|showMessage|게임 한판 종료 후 메세지를 출력하는 함수|

</br>

## 4. class LeeSedol
- 컴퓨터와 대결하는 클래스
- static으로 선언하여 싱글톤으로 사용한다.
- _Aset 객체의 오목 판 정보(Board)에 포인터로 접근하여 게임을 진행한다.

게임 초기에는 바둑돌이 놓일 때마다 가중치를 계산하여 다음에 놓일 최적의 위치를 계산한다. (참고 :https://ku-hug.tistory.com/2) 다만 게임이 진행 될 수록 실제 승리할 수 있는 수와 가중치를 통해 계산한 수가 달라지게 되므로, 바둑돌 위치를 통한 가중치 계산 외에도 실제 게임에 영향을 주는 경우(세개 이상 돌이 연속된 경우)를 따로 탐색하여 가중치를 부여한다. __게임 레벨이 높아질수록 더 많은 경우의 수를 탐색__ 하여 게임의 난이도를 어렵게 하였다.

### 멤버변수
|타입|변수명|내용|
|-|-|-|
|int|(* Board)[SIZE]|Aset 클래스의 멤버변수 Board에 접근하기 위한 포인터 (2차원 배열 접근)|
|int|weightBoard[SIZE][SIZE]|돌 배치에 따른 가중치를 저장하기 위한 2차원 배열|

### 멤버함수
|타입|함수명|내용|
|-|-|-|
|void|setBoard|멤버변수 (* Board)[SIZE]에 Aset 클래스의 멤버변수 Board를 저장하는 함수|
|pair<int,int>|computerTurn|바둑돌을 두기 위한 최적의 위치를 찾는 함수</br> 바둑돌 위치를 반환하고, 이를 그리는것은 GameProcessor 객체가 수행|
|void|gameForLevel_1|방어 가중치를 계산하기 위한 함수(레벨1)|
|void|gameForLevel_2|방어 가중치를 계산하기 위한 함수(레벨2)|
|void|gameForLevel_3|공격 가중치를 계산하기 위한 함수(레벨3)|
|void|gameForLevel_4|공격 가중치를 계산하기 위한 함수(레벨4)|

</br>

## 5. class CommunicationMode
- TCP/IP 통신으로 다른 컴퓨터의 유저와 게임하기 위해 구현된 클래스

### Class diagram
- 게임 진행을 위해 User 클래스와 마찬가지로 Aset, GameProcessor 클래스를 참조한다.

![image](https://user-images.githubusercontent.com/49704910/158114501-a7e28ea5-4792-41dd-9083-e7320546ad1c.png)

### 멤버함수
- TCP/IP 서버와 클라이언트는 같은 목적의 함수(초기화, 게임 진행)를 수행하지만 실행되는 코드는 다르다. 따라서 부모 클래스에서 이러한 함수를 가상함수로 선언하고, 이를 상속받아 자식 클래스에서 구현하도록 하였다.
- 상속구조

　 　　 ![image](https://user-images.githubusercontent.com/49704910/158114724-333f5516-1fab-42c3-833c-49cfb5570675.png) 

|타입|함수명|내용|
|-|-|-|
|void|initGame|멤버변수 (* Board)[SIZE]에 Aset 클래스의 멤버변수 Board를 저장하는 함수|
|virtual bool|doGame|상대편과 게임을 구현하기 위한  가상함수|
|virtual void|SocketInit|소켓을 초기화하고 설정하기 위한 가상함수|



</br>

## 프로그램 실행 설정 (Visual studio)
#### 소켓 라이브러리 추가
- 속성 > 링커 > 명령줄 > 추가옵션 > ws2_32.lib 추가
#### 인코딩 에러 발생시 
- 다른 이름으로 저장 > 고급 저장 옵션 > 유니코드 - 코드페이지 1200



</br>

 
