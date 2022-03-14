#include "_StartPage.h" 
#include "_User.h"
#include "_usrForClient.h"
#include "_usrForServer.h"
using namespace std;




int main() {

    _StartPage* ptrStartPage = new _StartPage();

    while (1) {

        int mode = ptrStartPage->openingPage();
        system("cls");

        bool isEnter = false;
        bool isWin = false;

        if (mode == 1) {
            _User* userTest = new _User();
            isWin = userTest->doGame();

        }

        else if (mode == 2 || mode == 3) { // TCP/IP mode

            if (mode == 2) {
                _usrForServer* ptrUsrServer = new _usrForServer();
                ptrUsrServer->SocketInit();
                isWin = ptrUsrServer->doGame(true);
                delete ptrUsrServer;
            }

            else if (mode == 3) {
                _usrForClient* ptrUsrClient = new _usrForClient();
                ptrUsrClient->SocketInit();
                isWin = ptrUsrClient->doGame(false);
                delete ptrUsrClient;
            }

            ptrStartPage->endingPage(isWin);
            Sleep(3000);

        }


        else return 0; // key q
    }


}


 