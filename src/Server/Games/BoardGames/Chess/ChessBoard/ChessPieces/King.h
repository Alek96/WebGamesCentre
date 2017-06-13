#ifndef KING_H
#define KING_H

#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <functional>

#include "ChessPiece.h"
#include "ChessPieceFactory.h"

class King : public ChessPiece
{
public:
	typedef std::shared_ptr<ChessPiece> ChessPiecePtr;
	typedef std::vector<ChessBoardPosition> vectorPath;
	King(ChessPiece::Color color);
	~King();

	static ChessPiecePtr createWhite();
	static ChessPiecePtr createBlack();

	vectorPath getPath(ChessBoardPosition position);
	std::string getName();
};

#endif //KING_H
