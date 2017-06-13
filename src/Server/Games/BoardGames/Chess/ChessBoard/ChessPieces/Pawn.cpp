#include "Pawn.h"

Pawn::Pawn(ChessPiece::Color color)
	: ChessPiece(color) {}

Pawn::~Pawn() {}

std::shared_ptr<ChessPiece> Pawn::createWhite()
{
	return std::make_shared<Pawn>(ChessPiece::Color::White);
}

std::shared_ptr<ChessPiece> Pawn::createBlack()
{
	return std::make_shared<Pawn>(ChessPiece::Color::Black);
}

std::vector<ChessBoardPosition> Pawn::getPath(ChessBoardPosition position)
{
	std::vector<ChessBoardPosition> vec;

	if (getColor() == ChessPiece::Color::White) {
		if (getPosition() - position == -8) {
			vec.push_back(position);
		}
		else if (getPosition() - position == -16 && getPosition() / 8 == 1) {
			ChessBoardPosition firstSquare = static_cast<ChessBoardPosition>(position - 8);
			vec.push_back(firstSquare);
			vec.push_back(position);
		}
	}
	else {
		if (getPosition() - position == 8) {
			vec.push_back(position);
		}
		else if (getPosition() - position == 16 && getPosition() / 8 == 6) {
			ChessBoardPosition firstSquare = static_cast<ChessBoardPosition>(position + 8);
			vec.push_back(firstSquare);
			vec.push_back(position);
		}
	}

	return vec;
}

std::string Pawn::getName()
{
	return std::string(std::string(color_ == ChessPiece::Color::White ? "White" : "Black") + std::string("Pawn"));
}