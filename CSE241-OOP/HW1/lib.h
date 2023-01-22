

#ifndef LIB_h
#define LIB_H
#include <vector>
#include <sstream>
#include <limits>

using namespace std;
/* enums*/
enum class peg_Type :int{
empty=1 , peg=2
};

typedef enum direction :int{
    right=114,left=108,up=117,down=100
}direction;

/* board*/
typedef std::vector<std::vector<peg_Type>> peg_board;

/*functions*/
bool peg_move(peg_board *board,int move_x,int move_y,direction dir,bool);
bool can_move(int, int ,direction , peg_board*,bool);
void print_board(const peg_board*);
void fill_board(peg_board*,int );
void fill_like_rectangular_board(peg_board*,int ,int ,int ,int ,int ,int ,int ,int );
void create_board(peg_board*,const int ,const int );
int get_random_int(int ,int );
void move_seperator(string , int* ,int* ,direction* );
bool is_move_syntax_valid(string, int, int );
bool is_game_finished(const peg_board *,int*,bool );
void get_computer_choice(int *move_x, int* move_y, direction* dir,const peg_board *board);
#endif