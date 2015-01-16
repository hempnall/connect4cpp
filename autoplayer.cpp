#include "autoplayer.h"
#include <iostream>

AutoPlayer::AutoPlayer(int player,int max_ply)
    : Player(player),max_depth(max_ply)
{



}

int AutoPlayer::getMove(Board b)
{

    b_ = b;
    analysePosition(colour_,0);
    return 3;

}


void AutoPlayer::analysePosition(
        int player /**< the player who's move it is at this ply */,
        int depth  /**< the depth of this ply */,
        int base_move /**< the root move being considered */
        )
{


  //   std::cout << std::endl << b_;

    if (depth == max_depth) {
        return;
    }

    for (int i=0;i<7;++i)   {

        if (b_.push_counter(i)) {
            analysePosition(3 - player, depth + 1);
            b_.pop_counter();
        }

    }

}
