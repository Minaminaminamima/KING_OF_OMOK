#include "_User.h"


_User::_User() {

    ptrAset = new _Aset();
    ptrLSD = new _LeeSedol();
    ptrGP = new _GameProcessor();
        
}


void _User::initGame(int level) {

    ptrAset->~_Aset();
    ptrAset = new _Aset();
    ptrLSD->setBoard(ptrAset->Board);
    ptrGP->setBoard(ptrAset->Board);

    ptrGP->drawBoard(level);
    ptrLSD->initLSDBoard();
}


bool _User::doGame() {
    ptrGP->initGame();
    int level = ADMIN_LEVEL;   

start: 
    initGame(level);
    bool user = true;
    bool winner = !user;
    int ret = -1;

    while (level!=5 && ret < 0) {      
        ret = ptrGP->userTurn(user);
        if (ret > 0) {
            winner = user;
            break;
        }
        ret = computerTurn(!user, level);

    }
     
    while (level==5 && ret < 0) {
       ret = computerTurn(user, level);
       if (ret > 0) {
            winner = !user;
            break;
       }
       ret = ptrGP->userTurn(!user);
       if (ret >= 0) { 
           return true;
       }
     }

 
    string str;
    if (winner == user) {
        str = "You Win!\nNext level is " + to_string(++level) + ".\nproceed?";
    } 
    else {
        str = "You loseee.\nDo you play again?";
        level = 0;
    }

    if (ptrGP->showMessage(str)) goto start;
    else return false;

}






int _User::computerTurn(bool user, int level) {
    auto next = ptrLSD->computerTurn(user, level);
    ptrGP->putStone(next.first, next.second, user);

    return ptrGP->isEnd(next.first, next.second, user);
}
