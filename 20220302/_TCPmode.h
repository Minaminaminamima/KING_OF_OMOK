#pragma once 
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "_GameProcessor.h"
#include "_Aset.h"



class _TCPmode {
public:
	/// /////////////////// For server
	WSADATA wasData;
	SOCKET hServSock;
	SOCKADDR_IN servAddr;

	SOCKET hClientSock;
	SOCKADDR clientAddr;

	/// /////////////////// For client
	//WSADATA wsaData;
	SOCKET hSocket; 

	static const int BUFSIZE = 102400;
	char message[BUFSIZE] = "";



public:


	_TCPmode();
	_Aset* ptrAset; // �� ���Ӹ��� �Ҹ� 
	_GameProcessor* ptrGP; // game process �κ� static  

	bool doGameForClient(bool isFirst);
	bool doGameForServer(bool isFirst);
	void initGame();

	void TCPserverInit();
	void TCPclientInit();
};





