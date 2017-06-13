#include "King.h"

King::King(ChessPiece::Color color)
	: ChessPiece(color) {}

King::~King() {}

std::shared_ptr<ChessPiece> King::createWhite()
{
	return std::make_shared<King>(ChessPiece::Color::White);
}

std::shared_ptr<ChessPiece> King::createBlack()
{
	return std::make_shared<King>(ChessPiece::Color::Black);
}

std::vector<ChessBoardPosition> King::getPath(ChessBoardPosition position)
{
	std::vector<ChessBoardPosition> vec;
	
	if (getPosition() != position) {
		for (int i = -1; i < 2; ++i) {
			for (int j = -1; j < 2; ++j) {
				if (getPosition() + i * 8 + j == position) {
					vec.push_back(static_cast<ChessBoardPosition>(getPosition() + i * 8 + j));
				}
			}
		}
	}

	return vec;
}

std::string King::getName()
{
	return std::string(std::string(color_ == ChessPiece::Color::White ? "White" : "Black") + std::string("King"));
}