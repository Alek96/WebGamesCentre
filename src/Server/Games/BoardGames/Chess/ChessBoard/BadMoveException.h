#ifndef BADMOVEEXCEPTION_H
#define BADMOVEEXCEPTION_H

#include <exception>

struct bad_move : public std::exception {
	virtual const char* what() const throw() {
		return "Figure can not move like that";
	}
};

#endif //BADMOVEEXCEPTION_H
