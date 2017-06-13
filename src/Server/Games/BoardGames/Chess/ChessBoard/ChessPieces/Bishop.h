#ifndef BISHOP_H
#define BISHOP_H

#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <functional>

#include "ChessPiece.h"
#include "ChessPieceFactory.h"

class Bishop : public ChessPiece
{
public:
	typedef std::shared_ptr<ChessPiece> ChessPiecePtr;
	typedef std::vector<ChessBoardPosition> vectorPath;
	Bishop(ChessPiece::Color color);
	~Bishop();

	static ChessPiecePtr createWhite();
	static ChessPiecePtr createBlack();

	vectorPath getPath(ChessBoardPosition position);
	std::string getName();
};

#endif //BISHOP_H
