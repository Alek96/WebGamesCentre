#include "Rook.h"

Rook::Rook(ChessPiece::Color color)
	: ChessPiece(color) {}

Rook::~Rook() {}

std::shared_ptr<ChessPiece> Rook::createWhite()
{
	return std::make_shared<Rook>(ChessPiece::Color::White);
}

std::shared_ptr<ChessPiece> Rook::createBlack()
{
	return std::make_shared<Rook>(ChessPiece::Color::Black);
}

std::vector<ChessBoardPosition> Rook::getPath(ChessBoardPosition position)
{
	std::vector<ChessBoardPosition> vec;
	
	auto fun = [&](int x) {
		for (int i = 1; getPosition() + x*i >= 0 && getPosition() + x*i < 64; ++i) {
			vec.push_back(static_cast<ChessBoardPosition>(getPosition() + x*i));
			if (getPosition() + x*i == position)
				return;
		}
	};

	if (getPosition() > position) {
		if ((getPosition() - position) / 8 == 0 && (getPosition() / 8 == position / 8))
			fun(-1);
		if ((getPosition() - position) % 8 == 0)
			fun(-8);
	}
	else {
		if ((position - getPosition()) / 8 == 0 && (getPosition() / 8 == position / 8))
			fun(1);
		if ((position - getPosition()) % 8 == 0)
			fun(8);
	}

	return vec;
}

std::string Rook::getName()
{
	return std::string(std::string(color_ == ChessPiece::Color::White ? "White" : "Black") + std::string("Rook"));
}