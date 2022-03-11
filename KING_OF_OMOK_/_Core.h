#pragma once
#include <winSock2.h> 
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream> 
#include <stdlib.h>  
using namespace std;


#define ADMIN_LEVEL 1; // default is 0 
#define SIZE 15
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


#define BLACK 0
#define GRAY 7
#define DARK_BLUE 1
#define LIGHT_BLUE 9
#define RED 12
#define YELLOW 14
#define WHITE 15


const int nX = (40 - SIZE - 1) / 2; // static int / const static int ?
const int nY = 11 - SIZE / 2;

 


static class _Core {
private :

public :

    void SetColor(int color);
    void SetColor(int color, int bgcolor);
    void gotoxy(int x, int y);

    void showCursor(bool input, int cursor_size);
    int getKey();
};
 