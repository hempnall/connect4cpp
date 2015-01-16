#include <iostream>
#include "game.h"
#include "manualplayer.h"
#include "autoplayer.h"

using namespace std;

int main()
{

    ManualPlayer p1(1);
    AutoPlayer p2(2,3);

    Game g(p1,p2);
    g.startGame();

    return 0;
}

