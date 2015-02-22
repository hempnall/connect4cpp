#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

class Player
{
public:
    int colour_;

    Player(int colour);
    virtual int getMove(Board& b) = 0;
};

#endif // PLAYER_H
