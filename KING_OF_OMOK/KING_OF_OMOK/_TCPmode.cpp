#include "_TCPmode.h";


void _TCPmode::TCPserverInit() {

	printf("wait for client......");
	// use Winsock
	WSAStartup(MAKEWORD(2, 2), &wasData);
	// socket 생성
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	// Binding For server
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(5555);
	bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));

	// listen : 접속자 대기
	listen(hServSock, 5);
	int clientLen = sizeof(clientAddr);
	hClientSock = accept(hServSock, (SOCKADDR*)&clientAddr, &clientLen);



}


void _TCPmode::TCPclientInit() {

	WSAStartup(MAKEWORD(2, 2), &wasData);

	hSocket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 자신의 IP
	servAddr.sin_port = htons(5555); // server 의 포트 정보 

	// 서버 접속
	connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr));

}



_TCPmode::_TCPmode() {
	ptrAset = new _Aset();
	ptrGP = new _GameProcessor();
}

void _TCPmode::initGame() {
	ptrGP->setBoard(ptrAset->Board);
	ptrGP->drawBoard(1);
}





bool _TCPmode::doGameForServer(bool user) {

	ptrGP->initGame();

	int ret = -1;
	bool isWin = false;

	char buff[6];
	buff[0] = 1;
	buff[1] = 0;
	buff[2] = 0;


	while (ret < 0) {

		/////////////// Server Turn 
		ptrGP->drawWhoseTurn(true);
		auto tmp = ptrGP->TCPTurn(user);
		buff[3] = (char)tmp.first;
		buff[4] = (char)tmp.second;
		send(hClientSock, buff, sizeof(buff), 0);
		ret = ptrGP->isEnd(tmp.first, tmp.second, user);
		if (ret > 0) {
			isWin = true;
			break;
		}



		/////////////// Client Turn
		ptrGP->drawWhoseTurn(false);
		recv(hClientSock, message, BUFSIZE, 0); // wait response (syncronize)

		int xx = (int)message[3];
		int yy = (int)message[4];

		ptrGP->putStone(xx, yy, !user);
		ret = ptrGP->isEnd(xx, yy, !user);
		if (ret > 0) break;

	}


	string str;
	if (isWin) str = "You Win!";
	else str = "looooose";

	ptrGP->showMessage(str);
	return true;


}




bool _TCPmode::doGameForClient(bool user) {

	ptrGP->initGame();

	bool isWin = false;
	int ret = -1;

	char buff[6];
	buff[0] = 1;
	buff[1] = 0;
	buff[2] = 0;


	while (ret < 0) {
		/////////////// server Turn

		ptrGP->drawWhoseTurn(false);
		int strLen = recv(hSocket, message, BUFSIZE, 0); // 동기화 
		int xx = (int)message[3];
		int yy = (int)message[4];
		ptrGP->putStone(xx, yy, !user);
		ret = ptrGP->isEnd(xx, yy, !user);
		if (ret > 0) break;


		/////////////// client Turn 
		ptrGP->drawWhoseTurn(true);
		pair<int, int> tmp = ptrGP->TCPTurn(user);
		buff[3] = (char)tmp.first;
		buff[4] = (char)tmp.second;
		send(hSocket, buff, sizeof(buff), 0);
		ptrGP->isEnd(tmp.first, tmp.second, user);
		if (ret > 0) {
			isWin = true;
			break;
		}
	}


	string str;
	if (isWin) str = "You Win!";
	else str = "looooose";

	ptrGP->showMessage(str);
	return true;

}






