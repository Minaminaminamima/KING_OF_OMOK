#pragma once
#include "_Core.h"


static class _StartPage {

private:
    static const int velo = 10;

public:

    _Core* corePtr = new _Core();

    int openingPage();

    void endingPage(bool win); 

};