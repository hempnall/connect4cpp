#include "board.h"
#include <cstring>
#include <iostream>
#include <vector>

#define DEBUG( x )  std::cout << "[DEBUG] " << x << std::endl;


std::map<const char*,int> profile::func_count_;
//std::map<const char*,boost::chrono::milliseconds> profile::func_time_;
profile::profile( const char* nm )
    : nm_(nm)
{
    func_count_[nm]++;
  //  start = boost::chrono::high_resolution_clock::now();
}


profile::~profile() {
//    boost::chrono::milliseconds ms = boost::chrono::duration_cast<boost::chrono::milliseconds> (boost::chrono::high_resolution_clock::now() - start);
//    func_time_[nm_] += ms;
}

void profile::print() {

    for ( auto& kvp : func_count_   )  {
        std::cout << kvp.first << "= [" << kvp.second << "," <<  "func_time_[kvp.first]" << "ms]" << std::endl;
    }

}

Board::Board(int* p, int c)
    : player(1)
{
    memset( board ,0, 42 * sizeof(int));
    std::vector<int> moves(p,p+c);

    for (auto& i : moves) {
        push_counter(i);
    }

    std::cout << *this;
}

Board::Board()
    : player(1)
{
    memset( board ,0, 42 * sizeof(int));

}


bool Board::push_counter(int col,bool switch_pl)   {

    PROFILE;

    if (col < 0 || col > 6 || colheights[col]==6) {
        return false;
    }

    board[col][colheights[col]]=player;
    //check_for_win(col,@colheights[col])
    colheights[col] += 1;


   // std::cout << "[push] " << col << std::endl;
    moves.push(  col );


    if (switch_pl)  {
        switch_player();
    }

    return true;
}


void Board::pop_counter()   {
    PROFILE;

    switch_player();
    int lastmove = moves.top();
    moves.pop();

    colheights[lastmove] -= 1;
    board[lastmove][colheights[lastmove]]=0;
}


std::ostream& operator<< (std::ostream& ostr, const Board& b)  {

    PROFILE;

    for (int row=5;row>=0;row--)    {
        //# draw board upside down

        for (int col=0;col < 7;++col)   {

            ostr <<  b.board[col][row] << " ";
        }

        ostr << std::endl;

    }

    return ostr;
}

int Board::win_in_direction(int player, int len,int goal, int x, int y, int dx, int dy) {
    PROFILE;

    if (len == goal)   {
        return 0;

    } else if (x<0||x>6||y<0||y>5)  {
        return 0 ;
    } else if (board[x][y] == player)   {
        return 1 + win_in_direction(player,len+1,goal,x+dx,y+dy,dx,dy);
    } else {
        return 0;
    }
}


bool Board::win_in_line(int player,  int goal, int x, int y, int dx, int dy) {
    PROFILE;

    int win1 = win_in_direction(player,0,goal,x,y,dx,dy);
  //  std::cout << "win1=" << win1 ;
    if (win1 == goal) return true;
    int win2 =   win_in_direction(player, 0,goal,x,y,-dx,-dy) -1;
   // std::cout << "win2=" << win2 ;

    if ((win1 + win2) == goal) return true;
    return false;
}

bool Board::win(int col, int row, int plyr) {

    PROFILE;

    if 	(   win_in_line(plyr,4,col,row,-1,1) ||
            win_in_line(plyr,4,col,row,-1,0)   ||
            win_in_line(plyr,4,col,row,-1,-1) ||
            4 == win_in_direction(plyr,0,4,col,row,0,-1)

         )
    {
            return true;
    }

    return false;

}

bool Board::win(int col, int row)   {
    PROFILE;
    return win(col,row,player);

}


bool Board::win() {
    PROFILE;
    return win(player);

}

bool Board::win(int plyr)    {
    PROFILE;

    if (moves.size() == 0)  {
        return false;
    }

    int lastmove = moves.top();
    int col = moves.top();
    int row = colheights[lastmove]-1;

    return win(col,row,plyr);

}

void Board::switch_player() {
    PROFILE;
    player = 3 - player;
}



