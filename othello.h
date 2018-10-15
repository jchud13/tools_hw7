/************************************************************
Othello Class
By Jared Chudzinski with Virtual functions from game.h
This holds the game board, an 8x8 board made up of symbols
Holds information on each space in the board
and can translate that information into color and a first move
************************************************************/

#include "game.h"
#include "piece.h"
#include "colors.h"
#include <iostream>
namespace main_savitch_14
{
  class game;

class Othello: public game
{
  public:
    Othello(); //calls Restart

    void restart();


    int get_moves()const{return x;}
    void next_move(){x++;}
    void display_status();
    void make_move(const std::string& move);
    bool is_legal(const std::string& move)const;

    bool search_right(int row, int col)const; //searches to the right
    bool search_left(int row, int col)const; //searches left
    bool search_up(int row, int col)const; //searches up
    bool search_down(int row, int col)const; //searches down
    bool search_upLeft(int row, int col)const; //searches for diagonal left and up
    bool search_upRight(int row, int col)const; //searches for diagonal right and up
    bool search_downLeft(int row, int col)const; //searches for diagonal left and down
    bool search_downRight(int row, int col)const; //searches for diagonal right and down
    void whoWinning()const;

    who next_mover( ) const
        { return (x % 2 == 0 ? HUMAN : COMPUTER); }
    who last_mover( ) const
  	    { return (x % 2 == 1 ? HUMAN : COMPUTER); }

    //Purely virtual
    game* clone( )const;
      void compute_moves(std::queue<std::string>& moves) const;
      int evaluate( ) const;
      bool is_game_over( ) const;



private:
  int x;
  int flippable[8];
  Piece board [8][8];
  char design[9];






};
}//namespace wrap closer
