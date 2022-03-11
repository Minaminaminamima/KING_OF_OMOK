#include "_GameProcessor.h"
 

void _GameProcessor::setBoard(int(*userBoard)[SIZE]) {
    Board = userBoard;
}

void _GameProcessor::initGame() {
    corePtr->showCursor(true, 100);
};



void _GameProcessor::putStone(int x, int y, bool turn) {

    const char* shape[] = { "●", "●" };
    int color[2] = { WHITE,BLACK };
    Board[y][x] = turn;

    corePtr->SetColor(color[turn], YELLOW);
    corePtr->gotoxy((x + nX) * 2, y + nY);
    printf("%s", shape[turn]);
    corePtr->SetColor(GRAY);
}


void _GameProcessor::moveCursor(int& x, int& y)
{
    if (x < 0)          x = 0;
    else if (y < 0)     y = 0;
    else if (x >= SIZE) x = SIZE - 1;
    else if (y >= SIZE) y = SIZE - 1;
    corePtr->gotoxy((x + nX) * 2, y + nY);
}


int _GameProcessor::checkTheRow(int x, int y, bool user) {

    int cnt = 0;
    while (x > 0 && Board[y][x - 1] == (int)user) x--;
    for (; x < SIZE && Board[y][x] == (int)user; x++) cnt++;

    return cnt;
}


int _GameProcessor::checkTheCol(int x, int y, bool user) {

    int cnt = 0;
    while (y > 0 && Board[y - 1][x] == (int)user) y--;
    for (; y < SIZE && Board[y][x] == (int)user; y++) cnt++;

    return cnt;
}

int _GameProcessor::checkTheDownCross(int x, int y, bool user) {

    int cnt = 0;
    while (x > 0 && y > 0 && Board[y - 1][x - 1] == (int)user) { y--; x--; }
    for (; y < SIZE && x < SIZE && Board[y][x] == (int)user; y++, x++) cnt++;

    return cnt;
}


int _GameProcessor::checkTheUpCross(int x, int y, bool user) {

    int cnt = 0;
    while (y < SIZE && x>0 && Board[y + 1][x - 1] == (int)user) { y++; x--; }
    for (; x < SIZE && y < SIZE && Board[y][x] == (int)user; x++, y--) cnt++;

    return cnt;
}



int _GameProcessor::isEnd(int x, int y, bool user) {

    // check the row
    if (checkTheRow(x, y, user) >= 5) return user;
    if (checkTheCol(x, y, user) >= 5) return user;
    if (checkTheDownCross(x, y, user) >= 5) return user;
    if (checkTheUpCross(x, y, user) >= 5) return user;

    return -1;
}
 

  
 

bool _GameProcessor::showMessage(string str) {

    std::string stringtoconvert = str;

    std::wstring temp = std::wstring(stringtoconvert.begin(), stringtoconvert.end());
    LPCWSTR lpcwstr = temp.c_str();

    if (MessageBoxW(NULL, lpcwstr, L"King of Omok", MB_YESNO) == IDYES) return true;
    else return false;
}



pair<int, int> _GameProcessor::TCPTurn(bool user) {

    int x = 0;
    int y = 0;
    bool isDone = false;
    int ret = -1;

    while (!isDone) {

        if (_kbhit()) {
            int ch = corePtr->getKey();

            switch (ch)
            {
            case UP:
                moveCursor(x, --y);
                break;

            case DOWN:
                moveCursor(x, ++y);
                break;

            case LEFT:
                moveCursor(--x, y);
                break;

            case RIGHT:
                moveCursor(++x, y);
                break;

            case ENTER:
                if (Board[y][x] != -1) continue;
                putStone(x, y, user);
                //ret = isEnd(x, y, user);
                isDone = true;
            }


        }


    }
    return { x,y };
}





int _GameProcessor::userTurn(bool user) {

    int x = 0;
    int y = 0;
    bool isDone = false;
    int ret = -1;

    while (!isDone) {


        if (_kbhit()) {
            int ch = corePtr->getKey();


            switch (ch)
            {
            case UP:
                moveCursor(x, --y);
                break;

            case DOWN:
                moveCursor(x, ++y);
                break;

            case LEFT:
                moveCursor(--x, y);
                break;

            case RIGHT:
                moveCursor(++x, y);
                break;

            case ENTER:
                if (Board[y][x] != -1) continue;
                putStone(x, y, user);
                ret = isEnd(x, y, user);
                isDone = true;
            }


        }


    }
    return ret;
}




void _GameProcessor::drawWhoseTurn(bool turn) {
     
    corePtr->gotoxy(nX * 2, nY - 1);
    corePtr->SetColor(YELLOW, BLACK);
    if (turn) printf("Your Turn           ");
    else printf("Other Turn              ");
}












void _GameProcessor::drawBoard(int level) {

    system("cls");
    const char* shape[] = { "┌ ", "┬ ", "┐ ", "├ ", "┼ ", "┤ ", "└ ", "┴ ", "┘ ", "■", "■" };

    corePtr->gotoxy(nX*2, nY-1);
    corePtr->SetColor(YELLOW, BLACK);
    printf("Level %d", level);

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            corePtr->SetColor(BLACK, YELLOW);

            int type = getLineNumber(i, j);
            corePtr->gotoxy((i + nX) * 2, j + nY);
            printf("%s", shape[type]);
            corePtr->SetColor(GRAY);
        }

} 
 





int _GameProcessor::getLineNumber(int x, int y)
{
    // 왼쪽 세로줄 
    if (x == 0)
    {
        // x, y가 다 0이면 왼쪽 상단 모서리 
        if (y == 0) return 0;
        // 왼쪽 하단 모서리 
        else if (y == SIZE - 1) return 6;
        // 왼쪽 세로줄 
        else return 3;
    }
    // 오른쪽 세로줄 
    else if (x == SIZE - 1)
    {
        // 오른쪽 상단 모서리 
        if (y == 0) return 2;
        // 오른쪽 하단 모서리 
        else if (y == SIZE - 1) return 8;
        // 오른쪽 세로줄 
        else return 5;
    }
    // 윗쪽 가로줄
    else if (y == 0)
    {
        // x, y가 다 0이면 왼쪽 상단 모서리 
        //if(x == 0) return 0;
        // 오른쪽 상단 모서리 
        //else if(x == SIZE - 1) return 2;
        // 위쪽 가로줄 
        //else return 1;
        return 1;
    }
    // 아래쪽 가로줄
    else if (y == SIZE - 1)
    {
        // 왼쪽 하단 모서리 
        //if(x == 0) return 6;
        // 오른쪽 하단 모서리 
        //else if(x == SIZE - 1) return 8;
        // 아래쪽 가로줄 
        //else return 7;
        return 7;
    }
    // 마지막 가운데 + 모양 
    else return 4;
}










