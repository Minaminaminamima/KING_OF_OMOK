#include "_StartPage.h" 


 


const char* STARTPAGE_KING[5][SIZE + 4] = {
    {"  ", "  ","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　"}, //0
    {"  ", "  ","■ ","　","■ ","　 ","■ ","　 ","■ ","　 ","　 ","■ ","　 ","　 ","■ ","■ ","　","　","　"}, //1
    {"  ", "  ","■ ","■ ","　 ","　 ","■ ","　 ","■ ","■ ","　 ","■ ","　 ","■ ","　 ","　 ","　","　","　"}, //2
    {"  ", "　","■ ","■ ","　 ","　 ","■ ","　 ","■ ","　 ","■ ","■ ","　 ","■ ","　 ","■ ","■ ","　","　"}, //3
    {"  ", "  ","■ ","　","■ ","　 ","■ ","　 ","■ ","　 ", "　 ","■ ","　 ","　 ","■ ","　 ","■ ","　","　"}, //4  // 0~4
};

const char* STARTPAGE_OF[4][SIZE + 4] = {
    {"  ", "　","　 ","　 ","　 ","　 ","■ ","■ ","　 ","　 ","■ ","■ ","■ ","　 ","　 ","　 ","　","　","　"}, //5
    {"  ", "　","　 ","　 ","　 ","■ ","　 ","　 ","■ ","　 ","■ ","　 ","　 ","　 ","　 ","　 ","　","　","　"}, //6
    {"  ", "　","　 ","　 ","　 ","■ ","　 ","　 ","■ ","　 ","■ ","■ ","■ ","　 ","　 ","　 ","　","　","　"},//7
    {"  ", "　","　 ","　 ","　 ","　 ","■ ","■ ","　 ","　 ","■ ","　 ","　 ","　 ","　 ","　 ","　","　","　"}, //8  // 5 ~8
};

const char* STARTPAGE_OMOK[6][SIZE + 4] = {
    {"　","　 ","■ ","■ ","　 ","■ ","　 ","　 ","　 ","■ ","　 ","■ ","■ ","　 ","■ ","　","　","■ ","  "}, //10
    {"　","■ ","　 ","　 ","■ ","■ ","■ ","　 ","■ ","■ ","■ ","　 ","　 ","■ ","■ ","　","■ ","　","  "},// 11
    {"　","■ ","　 ","　 ","■ ","■ ","　 ","■ ","　 ","■ ","■ ","　 ","　 ","■ ","■ ","■ ","　","　","  "}, //12
    {"　","■ ","　 ","　 ","■ ","■ ","　 ","■ ","　 ","■ ","■ ","　 ","　 ","■ ","■ ","　","■ ","　","  "}, //13
    {"　","　 ","■ ","■ ","　 ","■ ","　 ","■ ","　 ","■ ","　 ","■ ","■ ","　 ","■ ","　","　","　 ","  "}, //14 // 10~14
    {"  ", "　","　 ","　 ","　 ","　 ","　 ","　 ","　 ","　 ","　 ","　 ","　 ","　 ","　 ","　 ","　","　","　"} //9 
};
 
 



int _StartPage::openingPage() {

    corePtr->showCursor(false, 1);
    int fontcolor = DARK_BLUE; 


    // KING
    for (int cnt = SIZE-1 ; cnt >=0; cnt--) {
         
        for (int j = 0; j < SIZE ; j++) {
            for (int i = 0; i < SIZE + 4; i++) {
                    corePtr->SetColor(fontcolor, BLACK);
                     
                    corePtr->gotoxy((i + nX) * 2, cnt + j + nY);
                    if (j < 5) printf("%s", STARTPAGE_KING[j][i]);
                    else  printf("　"); 

            }
        }
        Sleep(velo*2);
    } // end of cnt


    // OF 
    int Yrange = 5;
    for (int cnt = SIZE - 1; cnt >= Yrange; cnt--) {

        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i < SIZE + 4; i++) {
                corePtr->SetColor(fontcolor, BLACK);

                corePtr->gotoxy((i + nX) * 2, cnt + j + nY);
                if (j < 4) printf("%s", STARTPAGE_OF[j][i]);
                else  printf("　"); 

            }
        }
        Sleep(velo*2);
    } // end of cnt


    Sleep(300);
    // OMOK
    Yrange = 9;
    fontcolor = RED;
        for (int j = 0; j < 6; j++) {
            for (int i = 0; i < SIZE + 4; i++) {
                corePtr->SetColor(RED, BLACK);
                corePtr->gotoxy((i + nX) * 2, Yrange + j + nY);
                printf("%s", STARTPAGE_OMOK[j][i]); 

            }
        }
    Sleep(velo*2);


    corePtr->SetColor(WHITE, BLACK);
    corePtr->gotoxy(2*nX+9, nY+17);
    printf("key 1 : game with computer"); 
    corePtr->gotoxy(2 * nX + 9, nY + 18);
    printf("key 2 : Enter as host");
    corePtr->gotoxy(2 * nX + 9, nY + 19);
    printf("key 3 : Enter as guest");

    Sleep(velo*3);

     
    while (1) {
        if (_kbhit()) {
            if (corePtr->getKey() == '1') return 1;
            else if (corePtr->getKey() == '2') return 2;
            else if (corePtr->getKey() == '3') return 3;
        }
        
    }
}








const char* ENDPAGE_FOR_WIN[14][SIZE + 4] = {
    {"  ", "  ","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　"}, //0
    {"  ", "■","　","　","　","■","　","■","　","■","　","　","　","■","　","　","■","　","　"}, //0
    {"  ", "■","　","　","　","■","　","■","　","■","■","　","　","■","　","　","■","　","　"}, //0
    {"  ", "■","　","　","　","■","　","■","　","■","■","　","　","■","　","　","■","　","　"}, //0
    {"  ", "■","　","　","　","■","　","■","　","■","　","■","　","■","　","　","■","　","　"}, //0
    {"  ", "■","　","　","　","■","　","■","　","■","　","■","　","■","　","　","■","　","　"}, //0
    {"  ", "■","　","■","　","■","　","■","　","■","　","■","　","■","　","　","■","　","　"}, //0
    {"  ", "■","　","■","　","■","　","■","　","■","　","■","■","■","　","　","■","　","　"}, //0
    {"  ", "  ","■","■","■","　","　","■","　","■","　","　","■","■","　","　","■","　","　"}, //0
    {"  ", "  ","■","　","■","　","　","■","　","■","　","　","　","■","　","　","　","　","　"}, //0
    {"  ", "  ","■","　","■","　","　","■","　","■","　","　","　","■","　","　","■","　","　"}, //0
    {"  ", "  ","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　"}, //0
    {"  ", "  ","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　"}, //0
};



const char* ENDPAGE_FOR_LOSE[14][SIZE + 4] = {
    {"  ", "  ","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　"}, //0
    {"■","　","　","　","　","■","■","■","　","　","　","■","■","　","　","■","■","■","■"}, //0
    {"■","　","　","　","■","　","　","　","■","　","■","　","　","■","　","■","　","　","　"}, //0
    {"■","　","　","　","■","　","　","　","■","　","■","　","　","■","　","■","　","　","　"}, //0
    {"■","　","　","　","■","　","　","　","■","　","■","　","　","　","　","■","　","　","　"}, //0
    {"■","　","　","　","■","　","　","　","■","　","　","■","　","　","　","■","■","■","■"}, //0
    {"■","　","　","　","■","　","　","　","■","　","　","　","■","　","　","■","　","　","　"}, //0
    {"■","　","　","　","■","　","　","　","■","　","　","　","　","■","　","■","　","　","　"}, //0
    {"■","　","　","　","■","　","　","　","■","　","　","　","　","■","　","■","　","　","　"}, //0
    {"■","　","　","　","■","　","　","　","■","　","　","　","　","■","　","■","　","　","　"}, //0
    {"■","■","■","■","　","■","■","■","　","　","■","■","■","　","　","■","■","■","■" }, //0
    {"  ", "  ","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　"}, //0
    {"  ", "  ","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　","　"}, //0

};







void _StartPage::endingPage(bool isWin) {

    Sleep(velo * 20);
    system("cls");
 
    corePtr->showCursor(false, 1);
    int fontcolor = isWin ? LIGHT_BLUE : RED; 

    const char* (*SHOWPAGE)[SIZE + 4] = isWin ? ENDPAGE_FOR_WIN : ENDPAGE_FOR_LOSE;

    for (int cnt = SIZE + 3; cnt >= 0; cnt--) {
        
        for (int j = 0; j < 13; j++) {
            for (int i = 0; i < SIZE + 4; i++) {
                corePtr->SetColor(fontcolor, BLACK);

                corePtr->gotoxy(cnt + (i + nX) * 2, j + (2+nY));
                printf("%s", SHOWPAGE[j][i]);

                if (i == SIZE + 3) { // remove margin
                    corePtr->gotoxy(cnt + 1 + (i + nX) * 2, j + nY);
                    printf("　");
                }
            }
        }
         
        Sleep(velo);
    } // end of cnt

    
}

 



 