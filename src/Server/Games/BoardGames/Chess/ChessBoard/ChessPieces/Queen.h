#ifndef QUEEN_H
#define QUEEN_H

#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <functional>

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
	typedef std::shared_ptr<ChessPiece> ChessPiecePtr;
	typedef std::vector<ChessBoardPosition> vectorPath;
	Queen(ChessPiece::Color color);
	~Queen();

	static ChessPiecePtr createWhite();
	static ChessPiecePtr createBlack();

	vectorPath getPath(ChessBoardPosition position);
	std::string getName();
};

#endif //QUEEN_H
