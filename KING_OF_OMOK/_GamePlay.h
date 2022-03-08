#pragma once
#include "_Core.h"  
#include "_LeeSedol.h"
using namespace std;

class leesedol;

class _GamePlay {

private:

    int Board[SIZE][SIZE] = { -1, };
    template <class T1, class T2> struct pair;


public:

    _Core* corePtr;
    _LeeSedol* lsdPtr;

    _GamePlay();

    void initeGame();
    void putStone(int y, int x, bool turn);
    void drawBoard();
    int getLineNumber(int x, int y);
     
    int isEnd(int x, int y, bool user);
    void moveCursor(int& x, int& y);
    bool showMessage(string str);

    int userTurn(bool user); // put the stone, check the game end
    int doGame();
    int checkTheRow(int x, int y, bool user);
    int checkTheCol(int x, int y, bool user);
    int checkTheDownCross(int x, int y, bool user);
    int checkTheUpCross(int x, int y, bool user);



    //////////////// tmp fun
    //bool leesedol();
    //bool whoTakeBlackStone();
    
};









