/******************************
The piece class
By: Jared Chudzinski
Has the ability to change a piece
from nothing to black or white
0 denotes nothing
1 denotes white
2 denotes black
*****************************/

class Piece{
	public:
		Piece();  //Constructor that sets space equal to zero
		void set_piece(int a); //Sets the space to whatever the parameter is
		int get_piece()const; //Returns the piece
		void flip();
		void search_up();
	private:
		int space;
};