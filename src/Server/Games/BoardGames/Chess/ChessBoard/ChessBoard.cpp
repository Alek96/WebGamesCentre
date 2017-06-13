#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	factory_.registerChessPiece(std::string("WhitePawn"), Pawn::createWhite);
	factory_.registerChessPiece(std::string("BlackPawn"), Pawn::createBlack);

	factory_.registerChessPiece(std::string("WhiteKnight"), Knight::createWhite);
	factory_.registerChessPiece(std::string("BlackKnight"), Knight::createBlack);

	factory_.registerChessPiece(std::string("WhiteBishop"), Knight::createWhite);
	factory_.registerChessPiece(std::string("BlackBishop"), Knight::createBlack);

	factory_.registerChessPiece(std::string("WhiteRook"), Knight::createWhite);
	factory_.registerChessPiece(std::string("BlackRook"), Knight::createBlack);

	factory_.registerChessPiece(std::string("WhiteQueen"), Knight::createWhite);
	factory_.registerChessPiece(std::string("BlackQueen"), Knight::createBlack);

	factory_.registerChessPiece(std::string("WhiteKing"), Knight::createWhite);
	factory_.registerChessPiece(std::string("BlackKing"), Knight::createBlack);

	createBoard();
}

ChessBoard::~ChessBoard()
{
}

bool ChessBoard::canMove(ChessBoardPosition positionA, ChessBoardPosition positionB)
{
	ChessPiecePtr ptr = getChessPiece(positionA);
	std::vector<ChessBoardPosition> vec = ptr->getPath(positionB);
	if (vec.empty())
		return false;
	auto preend = --vec.end();
	auto it = vec.begin();
	for (; it != preend; ++it) {
		if (getChessPiece(*it))
			return false;
	}
	if (getChessPiece(*it) && getChessPiece(*it)->getColor() == ptr->getColor())
		return false;
	return true;
}

void ChessBoard::move(ChessBoardPosition positionA, ChessBoardPosition positionB)
{
	if (!canMove(positionA, positionB))
		throw bad_move();
	
	setChessPiece(getChessPiece(positionA), positionB);
	board_[positionA].reset();
}

void ChessBoard::setChessPiece(ChessPiecePtr chessPiece, ChessBoardPosition position)
{
	chessPiece->setPosition(position);
	board_[position] = chessPiece;
}

std::shared_ptr<ChessPiece> ChessBoard::getChessPiece(ChessBoardPosition position)
{
	return board_[position];
}

std::string ChessBoard::getBoardForWhite()
{
	std::string str;

	for (int i = 7; i >= 0; --i) {
		for (int j = 0; j < 8; ++j) {
			if (board_[j + i * 8]) {
				str += (*board_[j + i * 8]).getName();
			}
			str += ", ";
		}
		str += "\n";
	}

	return str;
}

std::string ChessBoard::getBoardForBlack()
{
	std::string str;

	for (int i = 0; i < 8; ++i) {
		for (int j = 7; j >= 0; --j) {
			if (board_[j + i * 8]) {
				str += (*board_[j + i * 8]).getName();
			}
			str += ", ";
		}
		str += "\n";
	}

	return str;
}

void ChessBoard::createBoard()
{
	std::string str[64] = {
		/*1*/	"WhiteRook", "WhiteKnight", "WhiteBishop", "WhiteQueen", "WhiteKing", "WhiteBishop", "WhiteKnight", "WhiteRook",
		/*2*/	"WhitePawn", "WhitePawn", "WhitePawn", "WhitePawn", "WhitePawn", "WhitePawn", "WhitePawn", "WhitePawn",
		/*3*/	"", "", "", "", "", "", "", "",
		/*4*/	"", "", "", "", "", "", "", "",
		/*5*/	"", "", "", "", "", "", "", "",
		/*6*/	"", "", "", "", "", "", "", "",
		/*7*/	"BlackPawn", "BlackPawn", "BlackPawn", "BlackPawn", "BlackPawn", "BlackPawn", "BlackPawn", "BlackPawn",
		/*8*/	"BlackRook", "BlackKnight", "BlackBishop", "BlackQueen", "BlackKing", "BlackBishop", "BlackKnight", "BlackRook",
	};  //A B C D E F G H I

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			board_[j + i * 8].reset();
			if (str[j + i * 8] != "") {
				setChessPiece(factory_.create(str[j + i * 8]), static_cast<ChessBoardPosition>(j + i * 8));
			}
		}
	}

	setChessPiece(std::make_shared<Pawn>(ChessPiece::Color::White), ChessBoardPosition::A2);
}
