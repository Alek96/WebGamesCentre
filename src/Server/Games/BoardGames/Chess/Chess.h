#ifndef WEBGAMESCENTRE_CHESS_H
#define WEBGAMESCENTRE_CHESS_H

#include <exception>

#include "../BoardGame.h"
#include "ChessBoard/ChessBoard.h"

class Chess	: public BoardGame
{
public:
	Chess();
	~Chess();

	//ChessPiece* getBoard();

	bool checkMove();
	void move() throw (...);

	ChessBoard _chessBoard;

private:
};

#endif //WEBGAMESCENTRE_CHESS_H
