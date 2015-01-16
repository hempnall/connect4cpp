#ifndef AUTOPLAYER_H
#define AUTOPLAYER_H

#include "Board.h"
#include "Player.h"

class AutoPlayer : public Player
{
    Board b_;
    int max_depth;
    void analysePosition(int player,int depth );

public:
    AutoPlayer(int colour,int max_ply);
    virtual int getMove(Board b);


};

#endif // AUTOPLAYER_H
