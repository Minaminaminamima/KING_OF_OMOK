#pragma once
#include "_Core.h"  

static class _GameProcessor {

private :
    int(*Board)[SIZE];

public:
    // constructor
    //_GameProcessor(int(*userBoard)[SIZE]); 

    // pointers
    _Core* corePtr; 

    /// ////////////////////////////// init game
    void setBoard(int(*userBoard)[SIZE]);
    void initGame();
    void putStone(int y, int x, bool turn);
    void drawBoard(int level); 
    int getLineNumber(int x, int y);
    void drawWhoseTurn(bool usr);

    //////////////////// control the game
    int isEnd(int x, int y, bool user);
    void moveCursor(int& x, int& y);
    bool showMessage(string str); 

    /////////////////////////// sub-func
    int userTurn(bool user);
    pair<int, int> TCPTurn(bool user);
    int checkTheRow(int x, int y, bool user);
    int checkTheCol(int x, int y, bool user);
    int checkTheDownCross(int x, int y, bool user);
    int checkTheUpCross(int x, int y, bool user);
     
};