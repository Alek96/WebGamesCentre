#include "Knight.h"

Knight::Knight(ChessPiece::Color color)
	: ChessPiece(color) {}

Knight::~Knight() {}

std::shared_ptr<ChessPiece> Knight::createWhite()
{
	return std::make_shared<Knight>(ChessPiece::Color::White);
}

std::shared_ptr<ChessPiece> Knight::createBlack()
{
	return std::make_shared<Knight>(ChessPiece::Color::Black);
}

std::vector<ChessBoardPosition> Knight::getPath(ChessBoardPosition position)
{
	std::vector<ChessBoardPosition> vec;
	
	if (getPosition() + 6 == position)
		vec.push_back(static_cast<ChessBoardPosition>(getPosition() + 6));
	else if (getPosition() + 10 == position)
		vec.push_back(static_cast<ChessBoardPosition>(getPosition() + 10));
	else if (getPosition() + 15 == position)
		vec.push_back(static_cast<ChessBoardPosition>(getPosition() + 15));
	else if (getPosition() + 17 == position)
		vec.push_back(static_cast<ChessBoardPosition>(getPosition() + 17));

	if (getPosition() - 6 == position)
		vec.push_back(static_cast<ChessBoardPosition>(getPosition() - 6));
	else if (getPosition() - 10 == position)
		vec.push_back(static_cast<ChessBoardPosition>(getPosition() - 10));
	else if (getPosition() - 15 == position)
		vec.push_back(static_cast<ChessBoardPosition>(getPosition() - 15));
	else if (getPosition() - 17 == position)
		vec.push_back(static_cast<ChessBoardPosition>(getPosition() - 17));

	return vec;
}

std::string Knight::getName()
{
	return std::string(std::string(color_ == ChessPiece::Color::White ? "White" : "Black") + std::string("Knight"));
}