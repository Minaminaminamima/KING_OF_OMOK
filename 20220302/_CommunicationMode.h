#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "_GameProcessor.h"
#include "_Aset.h"
#include <string>


class _CommunicationMode {

protected :
	WSADATA wasData;
	SOCKET hServSock;
	SOCKADDR_IN servAddr;

	SOCKET hClientSock;
	SOCKADDR clientAddr;
	SOCKET hSocket;

	static const int BUFSIZE = 102400;
	char message[BUFSIZE] = "";
	char buff[6] = { 1,0,0,0,0,0 };


public:

	_Aset* ptrAset; 
	_GameProcessor* ptrGP; 


	void initGame() {
		ptrGP->setBoard(ptrAset->Board);
		ptrGP->drawBoard(1);
	}

	virtual bool doGame(bool usr) =0;
	virtual void SocketInit() =0;


};

 