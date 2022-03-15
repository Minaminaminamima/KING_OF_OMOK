#pragma once
#include "_CommunicationMode.h"

class _usrForClient : public _CommunicationMode{ 

private : 

	char server_IP[40] = "";


public: 
	_usrForClient(); 
	bool doGame(bool usr);
	void SocketInit();
};






