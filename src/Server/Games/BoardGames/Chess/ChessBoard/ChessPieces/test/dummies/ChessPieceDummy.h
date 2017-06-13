#include "../../ChessPiece.h"

class ChessPieceDummy : public ChessPiece
{
public:
	ChessPieceDummy(ChessPiece::Color color) : ChessPiece(color) {}
	~ChessPieceDummy() {}

	vectorPath getPath(ChessBoardPosition position) {
		return vectorPath();
	}
	std::string getName() {
		return std::string();
	}
};