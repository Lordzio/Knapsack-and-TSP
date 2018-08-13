#include "FileNotFoundException.h"
#include "stdafx.h"


const char * FileNotFoundException::what() const throw()
{
	return std::runtime_error::what();
}
