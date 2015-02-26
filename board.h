#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <stack>
#include <map>
//#include <tr1/chrono>
//#include <boost/chrono.hpp>


struct profile {
    const char* nm_;
 //  boost::chrono::high_resolution_clock::time_point start,end;
    static std::map<const char*,int> func_count_;
   // static std::map<const char*,boost::chrono::milliseconds> func_time_;
    static void print();
    profile( const char* nm );
    ~profile();
};
#define PROFILE //  profile __profiler__(__PRETTY_FUNCTION__);



class Board
{


    int colheights[7];
    std::stack<int> moves;


public:
    bool debug_;
    int player;
    Board();
    Board(int* p, int c   );
    int board[7][6];

    bool push_counter(int col,bool switch_pl = true);
    void pop_counter();

    bool get_last_move(int& col, int& row);
    int win_in_direction(int player, int len,int goal, int x, int y, int dx, int dy);
    bool win_in_line(int player, int goal, int x, int y, int dx, int dy);

    bool win(int col, int row);
    bool win(int col, int row,int plyr);
    bool win();
    bool win(int plyr);
    void switch_player();
};

struct DEBUGC {
    Board& b_;
    DEBUGC(Board&,bool cond=true);
    ~DEBUGC();
};

#define DEBUGON( b ,x ) DEBUGC debugger(b,x);
#define DEBUGOFF( b ,x ) DEBUGC debugger(b,false);
#define DEBUG( x ) { if (debugger.b_.debug_) std::cout << "[DEBUG] " << x; }
#define DEBUGB( x ) { if (debug_) std::cout << "[DEBUGB] " << x; }


std::ostream& operator << (std::ostream& ostr, const Board& b);

#endif // BOARD_H

