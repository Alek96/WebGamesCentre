#include "3rd-party/catch.hpp"
#include "dummies/ChessPieceDummy.h"
#include "../ChessPiece.h"
#include "../ChessPieceFactory.h"
#include "../Pawn.h"
#include "../Knight.h"
#include "../Bishop.h"
#include "../Rook.h"
#include "../Queen.h"
#include "../King.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace Catch;

SCENARIO("Test for ChessPiece", "[Chess]")
{
	GIVEN("A ChessPiece object with white color")
	{
		ChessPieceDummy piece(ChessPiece::Color::White);
		REQUIRE(piece.getColor() == ChessPiece::Color::White);

		WHEN("Set position") 
		{
			piece.setPosition(ChessBoardPosition::A1);
			THEN("Object has position")
			{
				REQUIRE(piece.getPosition() == ChessBoardPosition::A1);
				REQUIRE_FALSE(piece.getPosition() == ChessBoardPosition::A2);
				REQUIRE(piece.getColor() == ChessPiece::Color::White);

				WHEN("Change position")
				{
					piece.setPosition(ChessBoardPosition::C5);
					THEN("Object has different position")
					{
						REQUIRE_FALSE(piece.getPosition() == ChessBoardPosition::A1);
						REQUIRE(piece.getPosition() == ChessBoardPosition::C5);
						REQUIRE(piece.getColor() == ChessPiece::Color::White);
					}
				}
			}
		}
	}
	GIVEN("A ChessPiece object with black color")
	{
		ChessPieceDummy piece(ChessPiece::Color::Black);
		REQUIRE(piece.getColor() == ChessPiece::Color::Black);
		REQUIRE_FALSE(piece.getColor() == ChessPiece::Color::White);
	}
}

SCENARIO("Test for ChessPieceFactory", "[Chess]")
{
	GIVEN("A ChessPieceFactory object")
	{
		ChessPieceFactrory factory;
		THEN("Can not create new Piece that are not added")
		{
			REQUIRE_THROWS(factory.create("BlackPawn"));
			//REQUIRE_THROWS_AS(factory.create("BlackPawn"), const ChessPieceFactrory::bad_function_id()); ///niue dzia³a :/
		}

		WHEN("Add new create function")
		{
			factory.registerChessPiece(std::string("WhitePawn"), Pawn::createWhite);
			THEN("Can create new Piece")
			{
				std::shared_ptr<ChessPiece> ptr;
				REQUIRE_NOTHROW(ptr = factory.create("WhitePawn"));
				REQUIRE(ptr->getColor() == ChessPiece::Color::White);
			}
			THEN("Can not create new Piece that are not added")
			{
				REQUIRE_THROWS(factory.create("BlackPawn"));
			}
		}
	}
}

void checkPosition(ChessPiece &piece, ChessBoardPosition position, std::vector<ChessBoardPosition> vecPath = std::vector<ChessBoardPosition>())
{
	std::vector<ChessBoardPosition> path = piece.getPath(position);
	CHECK(path == vecPath);
}

SCENARIO("Test for Pawn", "[Chess]")
{
	GIVEN("A White Pawn object")
	{
		Pawn pawn(ChessPiece::Color::White);
		WHEN("Pawn is on position D2")
		{
			pawn.setPosition(ChessBoardPosition::D2);
			REQUIRE(pawn.getPosition() == ChessBoardPosition::D2);

			checkPosition(pawn, ChessBoardPosition::D3, { ChessBoardPosition::D3 });
			checkPosition(pawn, ChessBoardPosition::D4, { ChessBoardPosition::D3, ChessBoardPosition::D4 });
			checkPosition(pawn, ChessBoardPosition::D5, {});
		}
		WHEN("Pawn is on position A3")
		{
			pawn.setPosition(ChessBoardPosition::D3);
			REQUIRE(pawn.getPosition() == ChessBoardPosition::D3);

			checkPosition(pawn, ChessBoardPosition::D4, { ChessBoardPosition::D4 });
			checkPosition(pawn, ChessBoardPosition::D5, {});
			checkPosition(pawn, ChessBoardPosition::D6, {});
		}
	}
	GIVEN("A Black Pawn object")
	{
		Pawn pawn(ChessPiece::Color::Black);
		WHEN("Pawn is on position D7")
		{
			pawn.setPosition(ChessBoardPosition::D7);
			REQUIRE(pawn.getPosition() == ChessBoardPosition::D7);

			checkPosition(pawn, ChessBoardPosition::D6, { ChessBoardPosition::D6 });
			checkPosition(pawn, ChessBoardPosition::D5, { ChessBoardPosition::D6, ChessBoardPosition::D5 });
			checkPosition(pawn, ChessBoardPosition::D4, {});
		}
		WHEN("Pawn is on position D6")
		{
			pawn.setPosition(ChessBoardPosition::D6);
			REQUIRE(pawn.getPosition() == ChessBoardPosition::D6);

			checkPosition(pawn, ChessBoardPosition::D5, { ChessBoardPosition::D5 });
			checkPosition(pawn, ChessBoardPosition::D4, {});
			checkPosition(pawn, ChessBoardPosition::D3, {});
		}
	}
}

SCENARIO("Test for Knight", "[Chess]")
{
	GIVEN("A White Knight object")
	{
		Knight knight(ChessPiece::Color::White);
		WHEN("Knight is on position D3")
		{
			knight.setPosition(ChessBoardPosition::D3);
			REQUIRE(knight.getPosition() == ChessBoardPosition::D3);

			checkPosition(knight, ChessBoardPosition::C1, { ChessBoardPosition::C1 });
			checkPosition(knight, ChessBoardPosition::B2, { ChessBoardPosition::B2 });
			checkPosition(knight, ChessBoardPosition::B4, { ChessBoardPosition::B4 });
			checkPosition(knight, ChessBoardPosition::C5, { ChessBoardPosition::C5 });
			checkPosition(knight, ChessBoardPosition::E5, { ChessBoardPosition::E5 });
			checkPosition(knight, ChessBoardPosition::F4, { ChessBoardPosition::F4 });
			checkPosition(knight, ChessBoardPosition::F2, { ChessBoardPosition::F2 });
			checkPosition(knight, ChessBoardPosition::E1, { ChessBoardPosition::E1 });

			checkPosition(knight, ChessBoardPosition::B3, {});
			checkPosition(knight, ChessBoardPosition::D5, {});
			checkPosition(knight, ChessBoardPosition::E3, {});
			checkPosition(knight, ChessBoardPosition::D1, {});
		}
	}
}

SCENARIO("Test for Bishop", "[Chess]")
{
	GIVEN("A White Bishop object")
	{
		Bishop bishop(ChessPiece::Color::White);
		WHEN("Bishop is on position D2")
		{
			bishop.setPosition(ChessBoardPosition::D2);
			REQUIRE(bishop.getPosition() == ChessBoardPosition::D2);

			checkPosition(bishop, ChessBoardPosition::C3, { ChessBoardPosition::C3 });
			checkPosition(bishop, ChessBoardPosition::B4, { ChessBoardPosition::C3, ChessBoardPosition::B4 });
			checkPosition(bishop, ChessBoardPosition::A5, { ChessBoardPosition::C3, ChessBoardPosition::B4, ChessBoardPosition::A5 });
			checkPosition(bishop, ChessBoardPosition::E3, { ChessBoardPosition::E3 });
			checkPosition(bishop, ChessBoardPosition::F4, { ChessBoardPosition::E3, ChessBoardPosition::F4 });
			checkPosition(bishop, ChessBoardPosition::G5, { ChessBoardPosition::E3, ChessBoardPosition::F4, ChessBoardPosition::G5 });
			checkPosition(bishop, ChessBoardPosition::C1, { ChessBoardPosition::C1 });
			checkPosition(bishop, ChessBoardPosition::E1, { ChessBoardPosition::E1 });

			checkPosition(bishop, ChessBoardPosition::D3, {});
			checkPosition(bishop, ChessBoardPosition::D1, {});
			checkPosition(bishop, ChessBoardPosition::C2, {});
			checkPosition(bishop, ChessBoardPosition::E2, {});
		}
	}
}

SCENARIO("Test for Rook", "[Chess]")
{
	GIVEN("A White Rook object")
	{
		Rook rook(ChessPiece::Color::White);
		WHEN("Rook is on position D3")
		{
			rook.setPosition(ChessBoardPosition::D3);
			REQUIRE(rook.getPosition() == ChessBoardPosition::D3);

			checkPosition(rook, ChessBoardPosition::D4, { ChessBoardPosition::D4 });
			checkPosition(rook, ChessBoardPosition::D5, { ChessBoardPosition::D4, ChessBoardPosition::D5 });
			checkPosition(rook, ChessBoardPosition::D6, { ChessBoardPosition::D4, ChessBoardPosition::D5, ChessBoardPosition::D6 });
			checkPosition(rook, ChessBoardPosition::D7, { ChessBoardPosition::D4, ChessBoardPosition::D5, ChessBoardPosition::D6, ChessBoardPosition::D7 });
			checkPosition(rook, ChessBoardPosition::D8, { ChessBoardPosition::D4, ChessBoardPosition::D5, ChessBoardPosition::D6, ChessBoardPosition::D7, ChessBoardPosition::D8 });
			checkPosition(rook, ChessBoardPosition::D2, { ChessBoardPosition::D2 });
			checkPosition(rook, ChessBoardPosition::D1, { ChessBoardPosition::D2, ChessBoardPosition::D1 });

			checkPosition(rook, ChessBoardPosition::C3, { ChessBoardPosition::C3 });
			checkPosition(rook, ChessBoardPosition::B3, { ChessBoardPosition::C3, ChessBoardPosition::B3 });
			checkPosition(rook, ChessBoardPosition::A3, { ChessBoardPosition::C3, ChessBoardPosition::B3, ChessBoardPosition::A3 });
			checkPosition(rook, ChessBoardPosition::E3, { ChessBoardPosition::E3 });
			checkPosition(rook, ChessBoardPosition::F3, { ChessBoardPosition::E3, ChessBoardPosition::F3 });
			checkPosition(rook, ChessBoardPosition::G3, { ChessBoardPosition::E3, ChessBoardPosition::F3, ChessBoardPosition::G3 });
			checkPosition(rook, ChessBoardPosition::H3, { ChessBoardPosition::E3, ChessBoardPosition::F3, ChessBoardPosition::G3, ChessBoardPosition::H3 });

			checkPosition(rook, ChessBoardPosition::C2, {});
			checkPosition(rook, ChessBoardPosition::C4, {});
			checkPosition(rook, ChessBoardPosition::E4, {});
			checkPosition(rook, ChessBoardPosition::E2, {});
		}
	}
}

SCENARIO("Test for Queen", "[Chess]")
{
	GIVEN("A White Queen object")
	{
		Queen queen(ChessPiece::Color::White);
		WHEN("Queen is on position D3")
		{
			queen.setPosition(ChessBoardPosition::D3);
			REQUIRE(queen.getPosition() == ChessBoardPosition::D3);

			checkPosition(queen, ChessBoardPosition::D4, { ChessBoardPosition::D4 });
			checkPosition(queen, ChessBoardPosition::D5, { ChessBoardPosition::D4, ChessBoardPosition::D5 });
			checkPosition(queen, ChessBoardPosition::D6, { ChessBoardPosition::D4, ChessBoardPosition::D5, ChessBoardPosition::D6 });
			checkPosition(queen, ChessBoardPosition::D7, { ChessBoardPosition::D4, ChessBoardPosition::D5, ChessBoardPosition::D6, ChessBoardPosition::D7 });
			checkPosition(queen, ChessBoardPosition::D8, { ChessBoardPosition::D4, ChessBoardPosition::D5, ChessBoardPosition::D6, ChessBoardPosition::D7, ChessBoardPosition::D8 });
			checkPosition(queen, ChessBoardPosition::D2, { ChessBoardPosition::D2 });
			checkPosition(queen, ChessBoardPosition::D1, { ChessBoardPosition::D2, ChessBoardPosition::D1 });

			checkPosition(queen, ChessBoardPosition::C3, { ChessBoardPosition::C3 });
			checkPosition(queen, ChessBoardPosition::B3, { ChessBoardPosition::C3, ChessBoardPosition::B3 });
			checkPosition(queen, ChessBoardPosition::A3, { ChessBoardPosition::C3, ChessBoardPosition::B3, ChessBoardPosition::A3 });
			checkPosition(queen, ChessBoardPosition::E3, { ChessBoardPosition::E3 });
			checkPosition(queen, ChessBoardPosition::F3, { ChessBoardPosition::E3, ChessBoardPosition::F3 });
			checkPosition(queen, ChessBoardPosition::G3, { ChessBoardPosition::E3, ChessBoardPosition::F3, ChessBoardPosition::G3 });
			checkPosition(queen, ChessBoardPosition::H3, { ChessBoardPosition::E3, ChessBoardPosition::F3, ChessBoardPosition::G3, ChessBoardPosition::H3 });

			checkPosition(queen, ChessBoardPosition::C4, { ChessBoardPosition::C4 });
			checkPosition(queen, ChessBoardPosition::B5, { ChessBoardPosition::C4, ChessBoardPosition::B5 });
			checkPosition(queen, ChessBoardPosition::A6, { ChessBoardPosition::C4, ChessBoardPosition::B5, ChessBoardPosition::A6 });
			checkPosition(queen, ChessBoardPosition::E4, { ChessBoardPosition::E4 });
			checkPosition(queen, ChessBoardPosition::F5, { ChessBoardPosition::E4, ChessBoardPosition::F5 });
			checkPosition(queen, ChessBoardPosition::G6, { ChessBoardPosition::E4, ChessBoardPosition::F5, ChessBoardPosition::G6 });
			checkPosition(queen, ChessBoardPosition::H7, { ChessBoardPosition::E4, ChessBoardPosition::F5, ChessBoardPosition::G6, ChessBoardPosition::H7 });
			checkPosition(queen, ChessBoardPosition::C2, { ChessBoardPosition::C2 });
			checkPosition(queen, ChessBoardPosition::B1, { ChessBoardPosition::C2, ChessBoardPosition::B1  });
			checkPosition(queen, ChessBoardPosition::E2, { ChessBoardPosition::E2 });
			checkPosition(queen, ChessBoardPosition::F1, { ChessBoardPosition::E2, ChessBoardPosition::F1 });
		}
	}
}

SCENARIO("Test for King", "[Chess]")
{
	GIVEN("A White King object")
	{
		King king(ChessPiece::Color::White);
		WHEN("King is on position D3")
		{
			king.setPosition(ChessBoardPosition::D3);
			REQUIRE(king.getPosition() == ChessBoardPosition::D3);

			checkPosition(king, ChessBoardPosition::D4, { ChessBoardPosition::D4 });
			checkPosition(king, ChessBoardPosition::D2, { ChessBoardPosition::D2 });
			checkPosition(king, ChessBoardPosition::C3, { ChessBoardPosition::C3 });
			checkPosition(king, ChessBoardPosition::E3, { ChessBoardPosition::E3 });

			checkPosition(king, ChessBoardPosition::C4, { ChessBoardPosition::C4 });
			checkPosition(king, ChessBoardPosition::E4, { ChessBoardPosition::E4 });
			checkPosition(king, ChessBoardPosition::C2, { ChessBoardPosition::C2 });
			checkPosition(king, ChessBoardPosition::E2, { ChessBoardPosition::E2 });

			checkPosition(king, ChessBoardPosition::D5, {});
			checkPosition(king, ChessBoardPosition::D1, {});
			checkPosition(king, ChessBoardPosition::B3, {});
			checkPosition(king, ChessBoardPosition::F3, {});

			checkPosition(king, ChessBoardPosition::B5, {});
			checkPosition(king, ChessBoardPosition::F5, {});
			checkPosition(king, ChessBoardPosition::B1, {});
			checkPosition(king, ChessBoardPosition::F1, {});
		}
	}
}