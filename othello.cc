/************************************************************
Othello Class
By Jared Chudzinski with Virtual functions from game.h
This holds the game board, an 8x8 board made up of symbols
Holds information on each space in the board
and can translate that information into color and a first move
************************************************************/


#include "othello.h"
namespace main_savitch_14{

Othello::Othello(){
  x = 0;
  restart();
}

void Othello::display_status(){
  int count = 1; //This count allows numbers to be displayed on the side of the board
  std::cout << B_BLUE; //The background is blue because it made white and black pop, the gamepieces, and dulled the yellow, the nothing spaces
  std::cout << "  ";
  for(int n = 0; n < 8; n++){ // This is simply a design for loop
    design[0] = 'A';
    design[1] = 'B';
    design[2] = 'C';
    design[3] = 'D';
    design[4] = 'E';
    design[5] = 'F';
    design[6] = 'G';
    design[7] = 'H';
    std::cout << RED << design[n] << "  ";
  }
  std::cout << std::endl;
  for(int i = 0; i < 8; i++){
    std::cout << RED << count << " ";
    for(int j = 0; j < 8; j++){
      if(board[i][j].get_piece() == 0){
        std::cout << GREEN << " " << "|" << " "; //Nothing spaces are green @
      }
      if(board[i][j].get_piece() == 1){
        std::cout << WHITE << "%" << "|" << " "; //White spaces are white %
      }
      if(board[i][j].get_piece() == 2){
        std::cout << BLACK << "#" << "|" << " "; //Black spaces are black #
      }
    }
    count++;
    std::cout << endl;
  }
}

game* Othello::clone( )const{
  return new Othello(*this);
}

void Othello::compute_moves(std::queue<std::string>& moves) const{
  std::string one,two;
  while(!moves.empty()){
    moves.pop();
  }
  for (char i ='A'; i <='H'; i++){
    for (char j = '1'; j <='8'; j++){
      one = i;
      two =j;
      one +=two;
      if (is_legal(one)){
        moves.push(one);
      }
    }
  }
}

int Othello::evaluate( ) const{
  int count = 0, x, y;
  std::string move, tmp;
  for (char i = 'A'; i <= 'H'; i++){
    for (char j = '1';j<='8';j++ ){
      move = i;
      tmp = j;
      move += tmp;
      x = int(toupper(i)-'A');
      y = int(j-'1');
      if (move == "A1"|| move == "A8"|| move == "H1"|| move =="H8"){
        if (board[x][y].get_piece()==1){
          count += 2;
        }
        else{
           count -=2;
        }
      }
      else{
        if (board[x][y].get_piece()==1){
          count +=1;
        }
        else{
          count -=1;
        }
      }
    }
  }
  return count;
}

void Othello::restart(){

  for (int i = 0; i<8; i++){
    for (int j = 0; j<8; j++){
      if (i == 3 && j==3){
        board[i][j].set_piece(1);
      }
      else if (i == 4 && j==4){
        board[i][j].set_piece(1);
      }
      else if (i == 3 && j==4){
        board[i][j].set_piece(2);
      }
      else if (i == 4 && j==3){
        board[i][j].set_piece(2);
      }
      else{
        board[i][j].set_piece(0);
      }
    }
  }
}


void Othello::whoWinning()const
{
  int blackPiece = 0;
  int whitePiece = 0;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (board[i][j].get_piece() ==1)
      {

        whitePiece++;
      }
      if (board[i][j].get_piece() ==2)
      {

        blackPiece++;
      }
    }
  }
  //std::cout<< "Black has " << blackPiece << " pieces, and white has " << whitePiece << " pieces." <<std::endl;
}

bool Othello::is_game_over( ) const{ //add a case in case there is a time
 if(get_moves() == 6){
  return true;
 }
 else{
  return false;
 }
}


void Othello::make_move(const std::string& move)
{
    int skip;
    char first,second;
    int row, col;
    first = move.at(0);//grabs the letter in the string
    second = move.at(1);//grabs the number in the string
    if (first =='A'){
        col = 0;
    }
    else if (first =='B'){
      col = 1;
    }
    else if (first == 'C'){
      col = 2;
    }
    else if (first == 'D'){
      col = 3;
    }
    else if (first == 'E'){
      col = 4;
    }
    else if (first == 'F'){
      col = 5;
    }
    else if (first == 'G'){
      col = 6;
    }
    else if (first == 'H'){
      col = 7;
    }
    if (second == '1'){
      row = 0;
    }
    else if (second == '2'){
      row = 1;
    }
    else if (second == '3'){
      row = 2;
    }
    else if (second == '4'){
      row = 3;
    }
    else if (second == '5'){
      row = 4;
    }
    else if (second == '6'){
      row = 5;
    }
    else if (second == '7'){
      row = 6;
    }
    else if (second == '8'){
      row = 7;
    }
    if (get_moves() % 2 == 0)//black player
    {
      board[row][col].set_piece(2);
      if (search_right(row,col)==true){
        col++;
        while (board[row][col].get_piece()!=2){
          board[row][col].flip();
          col++;
        }
      }
      if (search_left(row,col)==true){
        col--;
        while (board[row][col].get_piece()!=2)
        {
          board[row][col].flip();
          col--;
        }
      }
      if (search_up(row,col)==true){
        row--;
        while (board[row][col].get_piece()!=2){
          board[row][col].flip();
          row--;
        }
      }
      if (search_down(row,col)==true){
        row++;
        while (board[row][col].get_piece()!=2){
          board[row][col].flip();
          row++;
        }
      }
      if (search_upLeft(row,col)==true){
        row--;
        col--;
        while (board[row][col].get_piece()!=2){
          board[row][col].flip();
          row--;
          col--;
        }
      }
      if (search_upRight(row,col)==true){
        row--;
        col++;
        while (board[row][col].get_piece()!=2){
          board[row][col].flip();
          row--;
          col++;
        }
      }
      if (search_downLeft(row,col)==true){
        row++;
        col--;
        while (board[row][col].get_piece()!=2){
          board[row][col].flip();
          row++;
          col--;
        }
      }
      if (search_downRight(row,col)==true){
        row++;
        col++;
        while (board[row][col].get_piece()!=2){
          board[row][col].flip();
          row++;
          col++;
        }
      }
    }
    else{ //white player
      board[row][col].set_piece(1);
      if(search_right(row, col)==true){
        col++;
        while(board[row][col].get_piece()!=1){
          board[row][col].flip();
          col++;
        }
      }
      if (search_left(row,col)==true){
        col--;
        while (board[row][col].get_piece()!=1){
          board[row][col].flip();
          col--;
        }
      }
      if (search_up(row,col)==true){
        row--;
        while (board[row][col].get_piece()!=1){
          board[row][col].flip();
          row--;
        }
      }
      if (search_down(row,col)==true){
        row++;
        while (board[row][col].get_piece()!=1){
          board[row][col].flip();
          row++;
        }
      }
      if (search_upLeft(row,col)==true){
        row--;
        col--;
        while (board[row][col].get_piece()!=1){
          board[row][col].flip();
          row--;
          col--;
        }
      }
      if (search_upRight(row,col)==true){
        row--;
        col++;
        while (board[row][col].get_piece()!=1)
        {
          board[row][col].flip();
          row--;
          col++;
        }
      }
      if (search_downLeft(row,col)==true){
        row++;
        col--;
        while (board[row][col].get_piece()!=1)
        {
          board[row][col].flip();
          row++;
          col--;
        }
      }
      if (search_downRight(row,col)==true){
        row++;
        col++;
        while (board[row][col].get_piece()!=1){
          board[row][col].flip();
          row++;
          col++;
        }
      }
    }
    next_move();
    whoWinning();
}

bool Othello::is_legal(const std::string& move)const{
  int skip;
  char first,second;
  int row, col;
  first = move.at(0);//grabs the letter in the string
  second = move.at(1);//grabs the number in the string
  if (first =='A'){
      col = 0;
  }
  else if (first =='B'){
    col = 1;
  }
  else if (first == 'C'){
    col = 2;
  }
  else if (first == 'D'){
    col = 3;
  }
  else if (first == 'E'){
    col = 4;
  }
  else if (first == 'F'){
    col = 5;
  }
  else if (first == 'G'){
    col = 6;
  }
  else if (first == 'H'){
    col = 7;
  }
  if (second == '1'){
    row = 0;
  }
  else if (second == '2'){
    row = 1;
  }
  else if (second == '3'){
    row = 2;
  }
  else if (second == '4'){
    row = 3;
  }
  else if (second == '5'){
    row = 4;
  }
  else if (second == '6'){
    row = 5;
  }
  else if (second == '7'){
    row = 6;
  }
  else if (second == '8'){
    row = 7;
  }
  if (board[row][col].get_piece() != 0)
  {
    return false;
  }

  if (search_right(row, col)
  ||search_left(row, col)
  ||search_up(row, col)
  ||search_down(row, col)
  ||search_upLeft(row, col)
  ||search_upRight(row,col)
  ||search_downLeft(row, col)
  ||search_downRight(row, col))
  {
    return true;
  }
  else
  {
    return false;
  }
  if (first=='A'||first=='B'||first=='C'||first=='D'||first=='E'||first=='F'||first=='G'||first=='H')
  {
    if (second=='1'||second=='2'||second=='3'||second=='4'||second=='5'||second=='6'||second=='7'||second=='8')
    {
      return true;
    }
  }
  else
  {
    return false;
  }

  //return true;
}


bool Othello::search_right(int row, int col)const //searches for a black piece to the right of the input
{
  col++;
  if (get_moves() % 2 == 0)
  {
    while (board[row][col].get_piece()!= 0&& col < 7)
    {
      if (board[row][col].get_piece() == 1)
      {
        col++;
        if(board[row][col].get_piece() == 2)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    while (board[row][col].get_piece()!= 0 && col < 7)
    {
      if (board[row][col].get_piece() == 2)
      {
        col++;
        if(board[row][col].get_piece() == 1)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
}

bool Othello::search_left(int row, int col)const
{
  col--;
  if (get_moves() % 2 == 0)
  {
    while (board[row][col].get_piece()!= 0&& col > 0)
    {
      if (board[row][col].get_piece() == 1)
      {
        col--;
        if(board[row][col].get_piece() == 2)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    while (board[row][col].get_piece()!= 0 && col > 0)
    {
      if (board[row][col].get_piece() == 2)
      {
        col--;
        if(board[row][col].get_piece() == 1)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }

  }
}


bool Othello::search_up(int row, int col)const
{
  row--;
  if (get_moves() % 2 == 0)
  {
    while (board[row][col].get_piece()!= 0&& row > 0)
    {
      if (board[row][col].get_piece() == 1)
      {
        row--;
        if(board[row][col].get_piece() == 2)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    while (board[row][col].get_piece()!= 0 && row > 0)
    {
      if (board[row][col].get_piece() == 2)
      {
        row--;
        if(board[row][col].get_piece() == 1)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
}

bool Othello::search_down(int row, int col)const
{
  row++;
  if (get_moves() % 2 == 0)
  {
    while (board[row][col].get_piece()!= 0&& row < 7)
    {
      if (board[row][col].get_piece() == 1)
      {
        row++;
        if(board[row][col].get_piece() == 2)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    while (board[row][col].get_piece()!= 0 && row < 7)
    {
      if (board[row][col].get_piece() == 2)
      {
        row++;
        if(board[row][col].get_piece() == 1)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
}
bool Othello::search_upLeft(int row, int col)const
{
  col--;
  row--;
  if (get_moves() % 2 == 0)
  {
    while (board[row][col].get_piece()!= 0&& row > 0 && col > 0)
    {
      if (board[row][col].get_piece() == 1)
      {
        col--;
        row--;
        if(board[row][col].get_piece() == 2)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    while (board[row][col].get_piece()!= 0 && row > 0 && col > 0)
    {
      if (board[row][col].get_piece() == 2)
      {
        col--;
        row--;
        if(board[row][col].get_piece() == 1)
        {
          return true;
        }
      }
      else
      {
        return false;
      }

    }
  }
}

bool Othello::search_upRight(int row, int col)const
{
  col++;
  row--;
  if (get_moves() % 2 == 0)
  {
    while (board[row][col].get_piece()!= 0&& row > 0 && col < 7)
    {
      if (board[row][col].get_piece() == 1)
      {
        col++;
        row--;
        if(board[row][col].get_piece() == 2)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    while (board[row][col].get_piece()!= 0 && row > 0 && col < 7)
    {
      if (board[row][col].get_piece() == 2)
      {
        col++;
        row--;
        if(board[row][col].get_piece() == 1)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }

}

bool Othello::search_downLeft(int row, int col)const
{
  col--;
  row++;
  if (get_moves() % 2 == 0)
  {
    while (board[row][col].get_piece()!= 0&& row < 7 && col > 0)
    {
      if (board[row][col].get_piece() == 1)
      {
        col--;
        row++;
        if(board[row][col].get_piece() == 2)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    while (board[row][col].get_piece()!= 0 && row < 7 && col > 0)
    {
      if (board[row][col].get_piece() == 2)
      {
        col--;
        row++;
        if(board[row][col].get_piece() == 1)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
}

bool Othello::search_downRight(int row, int col)const
{
  col++;
  row++;
  if (get_moves() % 2 == 0)
  {
    while (board[row][col].get_piece()!= 0&& row <7  && col < 7)
    {
      if (board[row][col].get_piece() == 1)
      {
        col++;
        row++;
        if(board[row][col].get_piece() == 2)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    while (board[row][col].get_piece()!= 0 && row < 7 && col < 7)
    {
      if (board[row][col].get_piece() == 2)
      {
        col++;
        row++;
        if(board[row][col].get_piece() == 1)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }
}

}//namespace wrap
