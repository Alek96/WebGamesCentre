#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <functional>

#include "ChessBoardPosition.h"
#include "BadMoveException.h"
#include "ChessPieces/ChessPiece.h"
#include "ChessPieces/Pawn.h"
#include "ChessPieces/Knight.h"
#include "ChessPieces/ChessPieceFactory.h"

class ChessBoard
{
public:
	typedef std::shared_ptr<ChessPiece> ChessPiecePtr;

	ChessBoard();
	~ChessBoard();

	bool canMove(ChessBoardPosition positionA, ChessBoardPosition positionB);
	void move(ChessBoardPosition positionA, ChessBoardPosition positionB);

	void setChessPiece(ChessPiecePtr chessPiece, ChessBoardPosition position);
	ChessPiecePtr getChessPiece(ChessBoardPosition position);

	std::string getBoardForWhite();
	std::string getBoardForBlack();

private:
	void createBoard();
	ChessPiecePtr board_[64];
	ChessPieceFactrory factory_;
};

#endif //CHESSBOARD_H
