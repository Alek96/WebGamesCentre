#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <functional>
#include <vector>

#include "../ChessBoardPosition.h"

class ChessPiece
{
public:
	typedef std::shared_ptr<ChessPiece> ChessPiecePtr;
	typedef std::vector<ChessBoardPosition> vectorPath;
	enum Color { White, Black };

	ChessPiece(ChessPiece::Color);
	virtual ~ChessPiece();

	virtual vectorPath getPath(ChessBoardPosition position) = 0;

	virtual std::string getName() = 0;
	void setPosition(ChessBoardPosition position);
	ChessBoardPosition getPosition();
	ChessPiece::Color getColor();

protected:
	const ChessPiece::Color color_;
	ChessBoardPosition position_;
};

#endif //CHESSPIECE_H
