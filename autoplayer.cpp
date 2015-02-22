#include "autoplayer.h"
#include <iostream>


#define DEBUG(x )  // std::cout << "[" << x << "]";
#define DEBUG2( x ) //  std::cout << "[" << x << "]";

Branch::Branch(Board& b, int move )
    : b_(b)
{
   // std::cout << "+[" << b.player << ":" << move << "]";
    PROFILE;
    isValid_ =  b.push_counter(move);
}


Branch::~Branch() {
    PROFILE;
    if (isValid_) {
      //  std::cout << "-";
        b_.pop_counter();
    }
}

AutoPlayer::AutoPlayer(int player,int max_ply)
    : Player(player),max_depth(max_ply),
      minPlayer_(3-player),maxPlayer_(player)
{
    std::cout << "minPlayer:" << minPlayer_ << " maxPlayer:" << maxPlayer_ << std::endl;
}


#define WIN_SCORE 100
#define MIN_SCORE 1000
#define DTHREE_SCORE 50
#define STHREE_SCORE 25

int AutoPlayer::getMove(Board& b)
{
    PROFILE;

    int alpha = -MIN_SCORE;
    int beta = MIN_SCORE;
    int index =  maximisePosition(b,0,alpha,beta);

    std::cout << "move chosen: " << index << std::endl;

    int move = 0 ;
    std::cout << "Player auto: please enter your move (0-6,9)";
    std::cin >> move;

    if (move == 9) {
        return index;
    } else {
        return move;
    }
}




int AutoPlayer::calculatePosition(int player, Board& b) {
    PROFILE;
   // DEBUG("L");std::cout << "\n";
    return 0;
}


int AutoPlayer::maximisePosition(
        Board &b_,
        int depth,
        int alpha,
        int beta)
{
    PROFILE;

    int player = maxPlayer_;
    int value  = -MIN_SCORE;
    int index = -1;
    int score=0;


    for (int i=0;i<  7 ;++i)   {
       // if (depth == 0) DEBUG( "\n\n" );
        DEBUG( "A==" << alpha << ":B==" << beta << ":V==" << score);
        Branch b(b_,i);

        if (b.isValid_) {
            DEBUG("V");
            if (b_.win(player)) {
                DEBUG2( "**W**" );
                score =  WIN_SCORE;
            } else {
                if (depth < max_depth) {

                    score = minimisePosition(b_, depth + 1,alpha , beta);
                } else {
                    score = calculatePosition(player,b_);
                }
            }

            if (score > alpha) {
                DEBUG("A=" << score);
                alpha = score;
            }
            if (score > value) {
                DEBUG( "IDX=" << i)
                index = i;
                value = score;
            }
            if (beta < alpha) {
                DEBUG("PRUNE_MAX:" << alpha << ":" << beta)
                break;
            }
        }
    }

    if (depth == 0) {
       // DEBUG( "\n\n");
        return index;
    } else {
        return value;
    }
}

int AutoPlayer::minimisePosition(
        Board& b_,
        int depth  /**< the depth of this ply */,
        int alpha,
        int beta
        )
{
    PROFILE;

    int player = minPlayer_;
    int value = MIN_SCORE;
    int score=0;
    DEBUG( "A==" << alpha << ":B==" << beta << ":V==" << score);

    for (int i =0; i<7 ; ++i)   {
        Branch b(b_,i);
        if (b.isValid_) {
            DEBUG("V");
            if (b_.win(player)) {
                DEBUG2("**W**");
                score =  -WIN_SCORE;
            } else {
                if (depth < max_depth) {
                    score = maximisePosition(b_, depth + 1,alpha , beta);
                } else {
                    score = calculatePosition(player,b_);
                }
            }

            if (score < beta) {
                DEBUG("B=" << score);
                beta = score;
            }
            if (score < value) {
                DEBUG("IDX=" << i);
                value = score;
            }
            if (beta < alpha) {
                DEBUG("PRUNE_MIN:" << alpha << ":" << beta);
                break;
            }
        }
    }
    return value;
}
