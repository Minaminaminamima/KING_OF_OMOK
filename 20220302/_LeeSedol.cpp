#include "_LeeSedol.h"



void _LeeSedol::initLSDBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            weightBoard[i][j] = 0; 
        }
    }
}
 
void _LeeSedol::setBoard(int(*userBoard)[SIZE]) {
    Board = userBoard;
}

bool _LeeSedol::isInside(int x, int y) {
    return !(x < 0 || y < 0 || x >= SIZE || y >= SIZE);
}


pair<int, int> _LeeSedol::computerTurn(bool user, int level) {
    
    /// except for level 5
    if (level == 5) {
        if (Board[SIZE / 2][SIZE / 2] == -1) return { SIZE / 2, SIZE / 2 };
    }

    /// check board condition
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) { 
            if (Board[i][j] != -1) weightBoard[i][j] = INF;
        }
    }

      
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
           
            if (Board[y][x] == -1) continue;
              
            else if (Board[y][x] == !user) {
                gameForLevel_1(y, x);
                if (level >= 2) gameForLevel_2(y, x);
            }
            else if (Board[y][x] == user){
                if (level >= 3) gameForLevel_3(y, x);
                if (level >= 4) gameForLevel_4(y, x);
            }

                for (int k = 0; k < DIR_SIZE; k++) {    
                    int next_x = x + dir_x[k];
                    int next_y = y + dir_y[k];
                    if (!isInside(next_x, next_y) || Board[next_y][next_x]!=-1) continue;
                    weightBoard[next_y][next_x] += (int)user == Board[next_y][next_x] ? 1 : -1;
            }
        }
    }
    
    MustCase();

    int check_y=SIZE/2, check_x=SIZE/2;
    int MIN = INF;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (Board[i][j]==-1 && weightBoard[i][j] <= MIN) {
                check_y = i;
                check_x = j;
                MIN = weightBoard[i][j];
            }
        }
    }

    
    return { check_x, check_y };
}




bool _LeeSedol::MustCase() {

    bool ret = false;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (Board[i][j] == -1) continue;

            // row
            int cnt = 1;
            for (int k = 1; k < 4; k++) {
                if (j + k < SIZE && Board[i][j + k] == Board[i][j]) cnt++;}
            if (cnt == 4) {
                if (j + 4 < SIZE && Board[i][j + 4] == -1) weightBoard[i][j + 4] = -INF;
                if (j - 1 >=0 && Board[i][j -1]==-1) weightBoard[i][j - 1] = -INF;
                ret = true;
            }


            // col
            cnt = 1;
            for (int k = 1; k < 4; k++) {
                if (i + k < SIZE && Board[i+k][j] == Board[i][j]) cnt++;
            }
            if (cnt == 4) {
                if (i + 4 < SIZE && Board[i + 4][j] == -1) weightBoard[i + 4][j] = -INF;
                if (i - 1 >=0  && Board[i -1 ][j] == -1) weightBoard[i -1 ][j] = -INF;
                ret = true;
            }

            // up-cross;

            cnt = 1;
            for (int k = 1; k < 4; k++) {
                if (i-k>=0 && j+k<SIZE && Board[i - k][j+k] == Board[i][j]) cnt++;
            }
            if (cnt == 4) {
                if (i - 4 >= 0 && j + 4 < SIZE && Board[i - 4][j + 4] == -1) weightBoard[i - 4][j + 4] = -INF;
                if (i + 1 <SIZE && j -1 >=0 && Board[i + 1][j - 1] == -1) weightBoard[i - 1][j + 1] = -INF;
                ret = true;
            }


            cnt = 1;
            for (int k = 1; k < 4; k++) {
                if (i + k <SIZE && j + k < SIZE && Board[i + k][j + k] == Board[i][j]) cnt++;
            }
            if (cnt == 4) {
                if (i + 4 >= 0 && j + 4 < SIZE && Board[i + 4][j + 4] == -1) weightBoard[i + 4][j + 4] = -INF;
                if (i -1 <SIZE && j -1 >=0 && Board[i -1 ][j -1 ] == -1) weightBoard[i - 1][j - 1] = -INF;
                ret = true;
            }


        }
    }


    return ret;

}





void _LeeSedol::gameForLevel_1(int y, int x) {

    bool flag = true;


    // Sequential Row Three
    for (int i = x+1; i < x + 3; i++) {
        if (!isInside(i, y) || (Board[y][i] != Board[y][x])) {
            flag = false;
            break;
        }
    }

    if (flag) {
        if (isInside(x - 1, y) && Board[y][x - 1] == -1) weightBoard[y][x - 1] = -100000;
        if (isInside(x + 3, y) && Board[y][x + 3] == -1) weightBoard[y][x + 3] = -100000;
    }


    // Sequential Columm Three
    flag = true;
    for (int j = y+1; j < y+ 3; j++) {
        if (!isInside(x, j) || (Board[j][x] != Board[y][x])) {
            flag = false;
            break;
        }
    }

    if (flag) {
        if (isInside(x, y-1) && Board[y-1][x] == -1) weightBoard[y-1][x] = -100000;
        if (isInside(x, y+3) && Board[y+3][x] == -1) weightBoard[y+3][x] = -100000;
    }


    // sequential Cross Down
    flag = true;
    for (int k = 1; k < 3; k++) {
            if (!isInside(x+k, y+k) || (Board[y+k][x+k] != Board[y][x])) {
                flag = false;
                break;
        }
    }

    if (flag) {
        if (isInside(x-1, y - 1) && Board[y - 1][x-1] == -1) weightBoard[y - 1][x-1] = -100000;
        if (isInside(x+3, y + 3) && Board[y + 3][x+3] == -1) weightBoard[y + 3][x+3] = -100000;
    }


    // sequential Cross UP
    flag = true;
    for (int k = 1; k < 3; k++) {
        if (!isInside(x + k, y - k) || (Board[y - k][x + k] != Board[y][x])) {
            flag = false;
            break;
        }
    }

    if (flag) {
        if (isInside(x - 1, y + 1) && Board[y + 1][x - 1] == -1) weightBoard[y + 1][x - 1] = -100000;
        if (isInside(x + 3, y - 3) && Board[y - 3][x + 3] == -1) weightBoard[y - 3][x + 3] = -100000;
    }

    return;
}





 

void _LeeSedol::gameForLevel_2(int y, int x) {

    bool flag = true; 

    // OXOO / OOXO case for row
    int cnt = 1;
    int tmp = (Board[y][x] + 1) % 2;
    for (int i = x + 1; i < x + 4; i++) {
        if (!isInside(i, y) || Board[y][i] == tmp) {
            flag = false;
            break;
        }
        if (Board[y][i] == Board[y][x]) cnt++;
    }

    if (flag && cnt >= 3) {
        for (int i = x + 1; i < x + 4; i++) {
            if (Board[y][i] == -1) weightBoard[y][i] = -90000;
        }
    }


    // OXOO / OOXO for columm
    flag = true;
    cnt = 1;
    for (int i = y + 1; i < y + 4; i++) {
        if (!isInside(x, i) || Board[i][x] == tmp) {
            flag = false;
            break;
        }
        if (Board[i][x] == Board[y][x]) cnt++;
    }

    if (flag && cnt >= 3) {
        for (int i = y + 1; i < y + 4; i++) {
            if (Board[i][x] == -1) weightBoard[i][x] = -90000;
        }
    }




    // OXOO / OOXO for up-cross
    flag = true;
    cnt = 1;
    for (int k = 1; k < 4; k++) {
        if (!isInside(x+k, y-k) || Board[y+k][x-k] == tmp) {
            flag = false;
            break;
        }
        if (Board[y-k][x+k] == Board[y][x]) cnt++;
    }

    if (flag && cnt >= 3) {
        for (int k = 1; k < 4; k++) {
            if (Board[y-k][x+k] == -1) weightBoard[y-k][x+k] = -90000;
        }
    }


    // OXOO / OOXO for down-cross
    flag = true;
    cnt = 1;
    for (int k = 1; k < 4; k++) {
        if (!isInside(x + k, y + k) || Board[y + k][x + k] == tmp) {
            flag = false;
            break;
        }
        if (Board[y + k][x + k] == Board[y][x]) cnt++;
    }

    if (cnt >= 3) {
        for (int k = 1; k < 4; k++) {
            if (Board[y + k][x + k] == -1) weightBoard[y + k][x + k] = -90000;
        }
    }


}
 

void _LeeSedol::gameForLevel_3(int y, int x) {

   // check row 
    int cnt = 0;
       for (int k = 1; k < 3; k++) {
           if (x+k<SIZE && Board[y][x+k] == Board[y][x]) cnt++;
       }
       if (cnt == 2) {
           if (isInside(x + 3, y) && Board[y][x + 3] == -1) {
               if (isInside(x + 4, y) && Board[y][x + 4] != (int)!Board[y][x]) weightBoard[y][x + 3] = -8000;
           }
           if (isInside(x - 1, y) && Board[y][x - 1] == -1) {
               if (isInside(x - 2, y) && Board[y][x - 2] != (int)!Board[y][x]) weightBoard[y][x - 1] = -8000;
           }
       }

       cnt = 0;
       for (int k = 1; k < 3; k++) {
           if (y + k > SIZE && Board[y + k][x] == Board[y][x]) cnt++;
       }
       if (cnt == 2) {

           if (isInside(x, y + 3) && Board[y + 3][x] == -1) {
               if (isInside(x, y + 4) && Board[y + 4][x] != (int)!Board[y][x]) weightBoard[y + 3][x] = -8000;
           }
           if (isInside(x, y - 1) && Board[y - 1][x] == -1) {
               if (isInside(x - 2, y) && Board[y][x - 2] != (int)!Board[y][x]) weightBoard[y - 1][x] = -8000;
           }
       }


       cnt = 0;
       for (int k = 1; k < 3; k++) {
           if (y - k<0 && x + k>SIZE && Board[y - k][x + k] == Board[y][x]) cnt++;
       }
       if (cnt == 2) {

           if (isInside(x + 3, y - 3) && Board[y - 3][x + 3] == -1) {
               if (isInside(x + 4, y - 4) && Board[y - 4][x + 4] != (int)!Board[y][x])  weightBoard[y - 3][x + 3] = -8000;
           }
           if (isInside(x - 1, y - 1) && Board[y - 1][x - 1] == -1) {
               if (isInside(x - 2, y - 2) && Board[y - 2][x - 2] != (int)!Board[y][x]) weightBoard[y + 1][x - 1] = -8000;
           }
       }



       cnt = 0;
       for (int k = 1; k < 3; k++) {
           if (x + k > SIZE && y + k > SIZE && Board[y + k][x + k] == Board[y][x]) cnt++;
       }

       if (cnt == 2) {

           if (isInside(x + 3, y + 3) && Board[y + 3][x + 3] == -1) {
               if (isInside(x + 4, y + 4) && Board[y + 4][x + 4] != (int)!Board[y][x])  weightBoard[y + 3][x + 3] = -8000;
           }
           if (isInside(x - 1, y - 1) && Board[y - 1][x - 1] == -1) {
               if (isInside(x - 2, y - 2) && Board[y - 2][x - 2] != (int)!Board[y][x])  weightBoard[y - 1][x - 1] = -8000;
           }

       }
}





void _LeeSedol::gameForLevel_4(int y, int x) {

    int eneymy = (int)!Board[y][x];

    // check row 
    int cnt = 0;
    for (int k = 1; k < 4; k++) {
        if(k+x>SIZE || Board[y][x + k] == eneymy) goto checkCol;
        if (Board[y][x + k] == Board[y][x]) cnt++;
    }
    if (cnt == 4) for (int k = 1; k < 4; k++) {
        if (Board[y][x + k] == -1) {
            weightBoard[y][x + k] = -8000;
            break;
        }
    }


checkCol:
    cnt = 0;
    for (int k = 1; k < 4; k++) { 
        if (k + y > SIZE || Board[y+k][x] == eneymy)  goto checkUpCross;
        if (Board[y+k][x] == Board[y][x]) cnt++;
    }
    if (cnt == 4) for (int k = 1; k < 4; k++) {
        if (Board[y + k][x] == -1) {
            weightBoard[y+k][x] = -8000;
            break;
        }
    }


checkUpCross:
    for (int k = 1; k < 4; k++) { 
        if ((y-k)<0  || (x+k)> SIZE || Board[y - k][x + k] == eneymy) goto checkDownCross;
        if (Board[y -k][x+k] == Board[y][x]) cnt++;
    }
    if (cnt == 4) for (int k = 1; k <4; k++) {
        if (Board[y - k][x + k] == -1) {
            weightBoard[y - k][x + k] = -8000;
            break;
        }
    }


checkDownCross:
    for (int k = 1; k < 4; k++) {
        if ((y + k) > SIZE || (x + k) > SIZE || Board[y + k][x + k] == eneymy) return;
        if (Board[y + k][x + k] == Board[y][x]) cnt++;
    }

    if (cnt == 4) for (int k = 1; k < 4; k++) {
        if (Board[y + k][x + k] == -1) {
            weightBoard[y + k][x + k] = -8000;
            break;
        }
    }

     

}