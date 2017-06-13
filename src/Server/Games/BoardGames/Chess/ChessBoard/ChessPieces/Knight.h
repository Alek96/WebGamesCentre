#ifndef KNIGHT_H
#define KNIGHT_H

#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <functional>

#include "ChessPiece.h"
#include "ChessPieceFactory.h"

class Knight : public ChessPiece
{
public:
	typedef std::shared_ptr<ChessPiece> ChessPiecePtr;
	typedef std::vector<ChessBoardPosition> vectorPath;
	Knight(ChessPiece::Color color);
	~Knight();

	static ChessPiecePtr createWhite();
	static ChessPiecePtr createBlack();

	vectorPath getPath(ChessBoardPosition position);
	std::string getName();
};

#endif //KNIGHT_H
