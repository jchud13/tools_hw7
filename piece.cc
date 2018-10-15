/************************
Implementation for piece
By Jared Chudzinski
************************/



#include "piece.h"

Piece::Piece(){
	space = 0;
}

void Piece::set_piece(int a){
	space = a;
}

int Piece::get_piece()const{
	return space;
}

void Piece::flip(){
	if(space == 2){
		space = 1;
	}
	else{
		space = 2;
	}
}
