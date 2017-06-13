#include "Bishop.h"
#include <cmath>

Bishop::Bishop(ChessPiece::Color color)
	: ChessPiece(color) {}

Bishop::~Bishop() {}

std::shared_ptr<ChessPiece> Bishop::createWhite()
{
	return std::make_shared<Bishop>(ChessPiece::Color::White);
}

std::shared_ptr<ChessPiece> Bishop::createBlack()
{
	return std::make_shared<Bishop>(ChessPiece::Color::Black);
}

std::vector<ChessBoardPosition> Bishop::getPath(ChessBoardPosition position)
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
		if ((getPosition() - position) % 7 == 0 && (getPosition() / 8 != position / 8))
			fun(-7);
		if ((getPosition() - position) % 9 == 0)
			fun(-9);
	}
	else {
		if ((position - getPosition()) % 7 == 0 && (getPosition() / 8 != position / 8))
			fun(7);
		if ((position - getPosition()) % 9 == 0)
			fun(9);
	}

	return vec;
}

std::string Bishop::getName()
{
	return std::string(std::string(color_ == ChessPiece::Color::White ? "White" : "Black") + std::string("Bishop"));
}