#pragma once  
#include "_GameProcessor.h"

class gamePlay;

static class _LeeSedol {

private:
    int(*Board)[SIZE]; 
    int weightBoard[SIZE][SIZE];
   
    const int INF = 99999999;
    const int DIR_SIZE = 8;

    const int dir_x[8] = { -1,0,1,-1,1,-1,0,1 };
    const int dir_y[8] = { -1,-1,-1,0,0,1,1,1 };


public:

    pair<int,int> computerTurn(bool user, int level); 

    bool isInside(int y, int x);
    void initLSDBoard();
    void setBoard(int(*userBoard)[SIZE]);

    void gameForLevel_1(int y, int x);
    void gameForLevel_2(int y, int x);
    pair<int, int> gameForLevel_3(int y, int x); // attack

};
   
 


 