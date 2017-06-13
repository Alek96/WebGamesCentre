#ifndef CHESSPIECEFACTORY_H
#define CHESSPIECEFACTORY_H

#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <functional>

#include "ChessPiece.h"

class ChessPieceFactrory {
public:
	struct bad_function_id: public std::exception{
		virtual const char* what() const throw() {
			return "Function not found in ChessPieceFactrory";
		}
	};

	typedef std::shared_ptr<ChessPiece> ChessPiecePtr;
	typedef std::function<ChessPiecePtr()> createFunction;
	bool registerChessPiece(std::string id, createFunction fun);
	ChessPiecePtr create(std::string id) throw (...);
private:
	typedef std::map < std::string, createFunction > Callbacks;
	Callbacks callbacks_;
};

#endif //CHESSPIECEFACTORY_H