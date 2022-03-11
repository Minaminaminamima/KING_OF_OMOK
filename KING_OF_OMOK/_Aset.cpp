#pragma once
#include "_Aset.h"


_Aset::_Aset() {
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			Board[i][j] = -1;
}