#pragma comment(lib, "ws2_32.lib")
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

        if (mode == -1) return 0;

        bool isEnter = false;
        bool isWin = false;



        // single mode
        if (mode == 1) { 
            _User* userTest = new _User();
            isWin = userTest->doGame(); 
        }


       // TCP/IP server mode
       else if (mode == 2) {
                _usrForServer* ptrUsrServer = new _usrForServer();
                ptrUsrServer->SocketInit();
                isWin = ptrUsrServer->doGame(true);
                delete ptrUsrServer; 
        }


       // TOP/IP Client mode
       else if (mode == 3) { 
                _usrForClient* ptrUsrClient = new _usrForClient();
                ptrUsrClient->SocketInit();
                isWin = ptrUsrClient->doGame(false);
                delete ptrUsrClient; 
        }



        ptrStartPage->endingPage(isWin);
        Sleep(3000);
              
    }


}


 