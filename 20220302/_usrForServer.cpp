#define _CRT_SECURE_NO_WARNINGS
#include "_usrForServer.h";


void _usrForServer::SocketInit() {

	printf("wait for client......");

	WSAStartup(MAKEWORD(2, 2), &wasData); 
	hServSock = socket(PF_INET, SOCK_STREAM, 0); 

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(5555);
	bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));
	 
	listen(hServSock, 5);
	int clientLen = sizeof(clientAddr);
	hClientSock = accept(hServSock, (SOCKADDR*)&clientAddr, &clientLen);


}



_usrForServer::_usrForServer() {
	ptrAset = new _Aset();
	ptrGP = new _GameProcessor();
}


bool _usrForServer::doGame(bool user) {

	initGame();
	ptrGP->initGame();

	int ret = -1;
	bool isWin = false;



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
		recv(hClientSock, message, BUFSIZE, 0);  

		int xx = (int)message[3];
		int yy = (int)message[4];

		ptrGP->putStone(xx, yy, !user);
		ret = ptrGP->isEnd(xx, yy, !user);
		if (ret > 0) break;

	}

	 
	return isWin;

}






