#include "3rd-party/catch.hpp"
#include "../ChessBoard.h"

#include <iostream>

using namespace Catch;

SCENARIO("Test for ChessBoard", "[Chess]")
{
	GIVEN("A ChessBoard object")
	{
		ChessBoard board;
		
		WHEN("outPut board")
		{
			std::cout << board.getBoardForWhite();
			std::cout << board.getBoardForBlack();
		}
		WHEN("Move a Pawn D2") 
		{
			THEN("Move one square D3")
			{
				REQUIRE(board.canMove(ChessBoardPosition::D2, ChessBoardPosition::D3));
				REQUIRE_NOTHROW(board.move(ChessBoardPosition::D2, ChessBoardPosition::D3));
				REQUIRE_FALSE(board.getChessPiece(ChessBoardPosition::D2));
				REQUIRE(board.getChessPiece(ChessBoardPosition::D3));
				//std::cout << board.getBoardForWhite();
				THEN("Move another one square")
				{
					REQUIRE(board.canMove(ChessBoardPosition::D3, ChessBoardPosition::D4));
					REQUIRE_NOTHROW(board.move(ChessBoardPosition::D3, ChessBoardPosition::D4));
					REQUIRE_FALSE(board.getChessPiece(ChessBoardPosition::D3));
					REQUIRE(board.getChessPiece(ChessBoardPosition::D4));
					//std::cout << board.getBoardForWhite();
				}
			}
			THEN("Move two squares D4")
			{
				REQUIRE(board.canMove(ChessBoardPosition::D2, ChessBoardPosition::D4));
				REQUIRE_NOTHROW(board.move(ChessBoardPosition::D2, ChessBoardPosition::D4));
				REQUIRE_FALSE(board.getChessPiece(ChessBoardPosition::D2));
				REQUIRE(board.getChessPiece(ChessBoardPosition::D4));
				//std::cout << board.getBoardForWhite();
				THEN("Move another one square")
				{
					REQUIRE(board.canMove(ChessBoardPosition::D4, ChessBoardPosition::D5));
					REQUIRE_NOTHROW(board.move(ChessBoardPosition::D4, ChessBoardPosition::D5));
					REQUIRE_FALSE(board.getChessPiece(ChessBoardPosition::D4));
					REQUIRE(board.getChessPiece(ChessBoardPosition::D5));
					//std::cout << board.getBoardForWhite();
				}
			}
			THEN("Move three squares D5")
			{
				REQUIRE_FALSE(board.canMove(ChessBoardPosition::D2, ChessBoardPosition::D5));
				REQUIRE_THROWS(board.move(ChessBoardPosition::D2, ChessBoardPosition::D5));
				REQUIRE(board.getChessPiece(ChessBoardPosition::D2));
				REQUIRE_FALSE(board.getChessPiece(ChessBoardPosition::D5));
			}
		}
		THEN("Move back one square D1")
		{
			REQUIRE_FALSE(board.canMove(ChessBoardPosition::D2, ChessBoardPosition::D1));
			REQUIRE_THROWS(board.move(ChessBoardPosition::D2, ChessBoardPosition::D1));
			REQUIRE(board.getChessPiece(ChessBoardPosition::D2));
		}
	}
}