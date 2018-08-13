#include "IndexOutOfBoundsException.h"
#include "stdafx.h"

const char * IndexOutOfBoundsException::what() const throw()
{
	return std::runtime_error::what();
}
