#pragma once
#include <string>
#include "_GameProcessor.h"
#include "_Aset.h"
#include "_LeeSedol.h"



class _User { 

public :

	_Aset* ptrAset; // 한 게임마다 소멸 
	_GameProcessor* ptrGP; // game process 부분 static
	_LeeSedol* ptrLSD; // AI static

	_User();
	bool doGame();
	void initGame(int level);
	int computerTurn(bool user, int level);
};






 