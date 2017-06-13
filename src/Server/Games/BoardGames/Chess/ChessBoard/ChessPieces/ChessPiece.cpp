#include "ChessPiece.h"

ChessPiece::ChessPiece(ChessPiece::Color color)
	:color_(color) {}

ChessPiece::~ChessPiece() {}

void ChessPiece::setPosition(ChessBoardPosition position)
{
	position_ = position;
}

ChessBoardPosition ChessPiece::getPosition()
{
	return position_;
}

ChessPiece::Color ChessPiece::getColor()
{
	return color_;
}
