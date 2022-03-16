#define _CRT_SECURE_NO_WARNINGS
#include "_usrForClient.h";


void _usrForClient::SocketInit() {

	WSAStartup(MAKEWORD(2, 2), &wasData);
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAddr, 0, sizeof(servAddr));

	printf("Enter the Server IP : (just enter -1 for default server IP)    ");
	scanf("%s", server_IP);
	if(strcmp(server_IP, "-1")==0) strcpy(server_IP, "127.0.0.1");

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(server_IP);  
	servAddr.sin_port = htons(5555); 
	 
	connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr));

}



_usrForClient::_usrForClient() {
	ptrAset = new _Aset();
	ptrGP = new _GameProcessor();
}


bool _usrForClient::doGame(bool user) {

	initGame();
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
		int strLen = recv(hSocket, message, BUFSIZE, 0);  
		int xx = (int) message[3];
		int yy = (int) message[4];
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


	return isWin;

}






