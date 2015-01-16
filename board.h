#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <stack>

class Board
{


    int colheights[7];
    std::stack<int> moves;


public:

    int player;
    Board();
    int board[7][6];

    bool push_counter(int col,bool switch_pl = true);
    void pop_counter();

    bool win_in_direction(int player,int len,int x,int y,int dx,int dy);
    bool win(int col, int row);
    bool win();
    void switch_player();
};


std::ostream& operator << (std::ostream& ostr, const Board& b);

#endif // BOARD_H

