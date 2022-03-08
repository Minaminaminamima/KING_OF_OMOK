#include "_StartPage.h" 
#include "_User.h"
using namespace std;

 
int main() {
    
   
    _StartPage* ptrStartPage = new _StartPage();
    ptrStartPage->openingPage(); 
     
    // KING_OF_OMOK //
    // Level 1. computer just depends sequential stones
    // Level 2. computer depends many other case
    // Level 3. computer attack for sequential stones
    // Level 4. computer attack for many other case
    // Level 5. turns change (computer first)

    
    _User* userTest = new _User(); 
    bool isWin = userTest->doGame();
    
    ptrStartPage->endingPage(isWin);
     
    
    while (1);
}


