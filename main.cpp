#include <iostream>
#include <vector>
#include "game.h"
#include "manualplayer.h"
#include "autoplayer.h"

using namespace std;

int main()
{

    {
//        int moves[] =  { 1,1,2,2,4,4 };
//        Board b(moves,6);
//        AutoPlayer p2(1,3);
//        cout << p2.getMove(b);
    }

    {
//        int moves[] =  { 1,1,2,2,4,3,1,4 };
//        Board b(moves,8);
//        AutoPlayer p2(1,3);
//        cout << p2.getMove(b);
    }

//    {
//        int moves[] =  { 2,2,3,3 };
//        Board b(moves,4);
//        AutoPlayer p2(1,3);
//        cout << p2.getMove(b);
//    }


    ManualPlayer p1(1);
    AutoPlayer p2(2,8);
//    //ManualPlayer p2(2);

    Game g(p1,p2);
    g.startGame();

    return 0;
}

