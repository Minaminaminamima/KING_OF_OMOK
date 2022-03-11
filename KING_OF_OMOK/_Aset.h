#pragma once
#include "_Core.h"

class _Aset {


private: // private
	int Board[SIZE][SIZE] = { -1, };

public:
	_Aset();
	friend class _User;
	friend class _TCPmode;

};