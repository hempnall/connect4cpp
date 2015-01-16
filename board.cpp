#include "board.h"
#include <cstring>
#include <iostream>

#define DEBUG( x ) // std::cout << "[DEBUG] " << x << std::endl;


Board::Board()
    : player(1)
{
    memset( board ,0, 42 * sizeof(int));

}


bool Board::push_counter(int col,bool switch_pl)   {

    if (col < 0 || col > 6 || colheights[col]==6) {
        return false;
    }

    board[col][colheights[col]]=player;
    //check_for_win(col,@colheights[col])
    colheights[col] += 1;
    moves.push(  col);

    if (switch_pl)  {
        switch_player();
    }
    return true;
}


void Board::pop_counter()   {
    switch_player();
    int lastmove = moves.top();
    moves.pop();
    colheights[lastmove] -= 1;
    board[lastmove][colheights[lastmove]]=0;
}


std::ostream& operator<< (std::ostream& ostr, const Board& b)  {

    for (int row=5;row>=0;row--)    {
        //# draw board upside down
        for (int col=0;col < 7;++col)   {
            ostr <<  b.board[col][row] << " ";
        }
        ostr << std::endl;
    }

}

bool Board::win_in_direction(int player, int len, int x, int y, int dx, int dy) {

    DEBUG("win_in_direction(" << player << "," << len << "," << x << "," << y << "," << dx << "," << dy << ")");

    DEBUG( "boardpos=" << board[x][y]);

    if (len == 4)   {
        return true;
    } else if (x<0||x>6||y<0||y>5)  {
        DEBUG("not in grid");
        return false;
    } else if (board[x][y] == player)   {
        return win_in_direction(player,len+1,x+dx,y+dy,dx,dy);
    } else {
        DEBUG("miscfail");
        return false;
    }
}

bool Board::win(int col, int row)   {

    DEBUG("win(" << col << "," << row << ")");

    if 	(
         (col >= 3 &&
                (win_in_direction(player,0,col,row,-1,0) ||
                 win_in_direction(player,0,col,row,-1,1) ||
                 win_in_direction(player,0,col,row,-1,-1)
                 )
         )
         ||
         (col <= 3 &&
                (win_in_direction(player,0,col,row,1,0) ||
                 win_in_direction(player,0,col,row,1,1) ||
                 win_in_direction(player,0,col,row,1,-1)
                 )
          )
         ||
         (row>=3 &&
                    win_in_direction(player,0,col,row,0,-1))
         )
    {
            return true;
    }


}

bool Board::win()    {


    if (moves.size() == 0)  {
        return false;
    }

    int lastmove = moves.top();
    int col = moves.top();
    int row = colheights[lastmove]-1;


    return win(col,row);

}

void Board::switch_player() {
    player = 3 - player;
}
