#include "ChessPieceFactory.h"

bool ChessPieceFactrory::registerChessPiece(std::string id, createFunction fun)
{
	Callbacks::const_iterator it = callbacks_.find(id);
	if (it == callbacks_.end()) {
		callbacks_.insert(Callbacks::value_type(id, fun));
		return true;
	}
	else
		return false;
}

std::shared_ptr<ChessPiece> ChessPieceFactrory::create(std::string id)
{
	Callbacks::const_iterator it = callbacks_.find(id);
	if (it == callbacks_.end()) {
		throw bad_function_id();
	}
	return (it->second)();
}
