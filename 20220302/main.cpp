#include "_StartPage.h" 
#include "_User.h"
#include "_usrForClient.h"
#include "_usrForServer.h"
using namespace std;




int main() {


    _StartPage* ptrStartPage = new _StartPage();
    int mode = ptrStartPage->openingPage();
    system("cls");

    bool isEnter = false;
    bool isWin = false;

    if (mode == 1) {
        // KING_OF_OMOK //
        // Level 1. computer just depends sequential stones
        // Level 2. computer depends many other case
        // Level 3. computer attack for sequential stones
        // Level 4. computer attack for many other case
        // Level 5. turns change (computer first)


        _User* userTest = new _User();
        isWin = userTest->doGame();

    }

    else if (mode == 2) {
        _usrForServer* ptrUsrServer = new _usrForServer();
        ptrUsrServer->SocketInit();
        isWin = ptrUsrServer->doGame(true);
    }

    else if (mode == 3) {
        _usrForClient* ptrUsrClient = new _usrForClient();
        ptrUsrClient->SocketInit();
        isWin = ptrUsrClient->doGame(false);
    }

    ptrStartPage->endingPage(isWin);

    while (1);

}


 