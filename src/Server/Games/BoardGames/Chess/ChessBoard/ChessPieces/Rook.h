#ifndef ROOK_H
#define ROOK_H

#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <functional>

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
	typedef std::shared_ptr<ChessPiece> ChessPiecePtr;
	typedef std::vector<ChessBoardPosition> vectorPath;
	Rook(ChessPiece::Color color);
	~Rook();

	static ChessPiecePtr createWhite();
	static ChessPiecePtr createBlack();

	vectorPath getPath(ChessBoardPosition position);
	std::string getName();
};

#endif //ROOK_H
