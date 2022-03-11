#include "_TCPmode.h"
#include "_StartPage.h" 
#include "_User.h"
using namespace std;

 
int main() {


    _StartPage* ptrStartPage = new _StartPage();
    int mode = ptrStartPage->openingPage();
    system("cls");

    bool isEnter = false;

    if (mode == 1) {
        // KING_OF_OMOK //
        // Level 1. computer just depends sequential stones
        // Level 2. computer depends many other case
        // Level 3. computer attack for sequential stones
        // Level 4. computer attack for many other case
        // Level 5. turns change (computer first)


        _User* userTest = new _User();
        bool isWin = userTest->doGame();

        ptrStartPage->endingPage(isWin);
    }

    else if (mode == 2) {
        _TCPmode* TCPTest = new _TCPmode();
        TCPTest->TCPserverInit();
        TCPTest->initGame();
        TCPTest->doGameForServer(true);
    }


    else if (mode == 3) {
        _TCPmode* TCPTest = new _TCPmode();
        TCPTest->TCPclientInit();
        TCPTest->initGame();
        TCPTest->doGameForClient(false);
    }


}