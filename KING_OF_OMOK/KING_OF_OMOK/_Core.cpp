#include "_Core.h" 




void _Core::SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void _Core::SetColor(int color, int bgcolor) {

    color &= 0xf;
    bgcolor &= 0xf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

void _Core::gotoxy(int x, int y)
{
    COORD XY = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}


void _Core::showCursor(bool input, int cursor_size) {
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = input; //cursor -> Visible is TRUE / FALSE
    cursorInfo.dwSize = cursor_size; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}



int _Core::getKey()
{
    int ch;

    ch = _getch();
    if (ch == 0 || ch == 0xE0) ch = _getch();

    return ch;
}
