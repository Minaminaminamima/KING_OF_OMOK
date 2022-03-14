#pragma once
#include "_CommunicationMode.h"

class _usrForServer : public _CommunicationMode { 


public:
	_usrForServer();
	bool doGame(bool usr);
	void SocketInit();
};






