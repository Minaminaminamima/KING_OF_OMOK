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

    int mul = 0;

    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
           
            if (Board[y][x] == -1) continue;

            else if (Board[y][x] == (int)user) {
                mul = 1;
                if (level >= 3) { 
                    auto tmp = gameForLevel_3(y, x);
                    if (tmp.first != 0 && tmp.second != 0) return { tmp.first, tmp.second };
                }
            }
            else { // Board[y][x] != (int) user
                gameForLevel_1(y, x);
                if (level >= 2) gameForLevel_2(y, x); 
                mul = -1;
            }

            for (int k = 0; k < DIR_SIZE; k++) { 
                
                int next_x = x + dir_x[k];
                int next_y = y + dir_y[k];

                if (!isInside(next_x, next_y) || Board[next_y][next_x]!=-1) continue;
                weightBoard[next_y][next_x] += mul;
            }
        }
    }





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
            if (Board[y][i] == -1) weightBoard[y][i] = -900000;
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
            if (Board[i][x] == -1) weightBoard[i][x] = -900000;
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
            if (Board[y-k][x+k] == -1) weightBoard[y-k][x+k] = -900000;
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
            if (Board[y + k][x + k] == -1) weightBoard[y + k][x + k] = -900000;
        }
    }


}



pair<int, int> _LeeSedol::gameForLevel_3(int y, int x) {

   // check row 
       for (int k = 1; k < 3; k++) {
           if (Board[y][x+k] != (int)Board[y][x]) goto checkCol;
       }
       if (isInside(x + 3, y) && Board[y][x+3] ==-1 ) return { x + 3, y };
       if (isInside(x - 1, y) && Board[y][x-1] == -1) return { x - 1, y };

   checkCol :
       for (int k = 1; k < 3; k++) {
           if (Board[y+k][x] != (int)Board[y][x]) goto checkUpCross;
       }

       if (isInside(x, y+3) && Board[y+3][x] == -1) return { x, y + 3 };
       if (isInside(x, y-1) && Board[y-1][x] == -1) return { x, y - 1 };


   checkUpCross:
       for (int k = 1; k < 3; k++) {
           if (Board[y - k][x+k] != (int)Board[y][x]) goto checkDownCross;
       }

       if (isInside(x+3, y-3) && Board[y - 3][x+3] == -1) return { x+3, y - 3 };
       if (isInside(x-1, y-1) && Board[y - 1][x-1] == -1) return { x-1, y - 1 };



   checkDownCross :
       for (int k = 1; k < 3; k++) {
           if (Board[y + k][x + k] != (int)Board[y][x]) goto nothing;
       }

       if (isInside(x + 3, y + 3) && Board[y + 3][x + 3] == -1) return { x + 3, y + 3 };
       if (isInside(x - 1, y - 1) && Board[y - 1][x - 1] == -1) return { x - 1, y - 1 };


    nothing : 
       return { 0,0 };

}
