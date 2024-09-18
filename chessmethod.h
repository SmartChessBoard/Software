#pragma once//remove for Workwi

#include <iostream>//remove for Workwi
#include <cmath>//remove for Workwi
#include <string>//remove for Workwi

enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum Color { WHITE, BLACK, NONE };

class Square
{
	
	Piece piece;
	Color color;
	int x, y;
public:
	void setSpace(Square*);
	void setEmpty();
	void setupPiece(Piece, Color);
	Piece getPiece();
	Color getColor();
	Square();
};

class Board
{
	Square square[8][8];
	Color turn=WHITE;
	int IndexConverter(int row, int col);
	int* ShowAllKnightMoves(int row, int col);
	int* ShowAllBishopMoves(int row, int col);
	int* ShowRook(int row, int col);
	int* ShowPawn(int row, int col);
	int* ShowAllQueenMoves(int row, int col);
	bool moveKnight(int row, int col, int rowUpdated, int ColUpdated);
	bool moveBishop(int row, int col, int rowUpdated, int ColUpdated);
	bool moveRook(int row, int col, int rowUpdated, int ColUpdated);
	bool moveQueen(int row, int col, int rowUpdated, int ColUpdated);
	bool movePawn(int row, int col, int rowUpdated, int ColUpdated);
	bool moveKing(int row, int col, int rowUpdated, int ColUpdated);
	bool makeMove(int x1, int y1, int x2, int y2);
	void printBoard();
	
public:
	Square* getSquare(int x, int y) {
		return &square[x][y];
	}
	void setSquare(Square * s, int x, int y){
		square[x][y]=*s;
	}
	bool doMove();

	int getCol();
	int getRow();
	
	int row = getRow();
	int col = getCol();
	
	int getColUpdated();
	int getRowUpdated();

	int RowUpdated = getRowUpdated();
	int ColUpdated = getColUpdated();
	

	void testing();
	int IndexConverter(int row, int col);
	
	void createChessBoard();
	bool playGame();
};
