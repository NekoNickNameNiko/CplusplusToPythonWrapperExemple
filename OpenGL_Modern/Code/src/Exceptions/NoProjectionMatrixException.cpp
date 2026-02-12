#include "NoProjectionMatrixException.h"

Bwt::Core::Debug::Exceptions::NoProjectionMatrixException::NoProjectionMatrixException(std::string msg)
	: std::exception(msg.c_str()), message(msg)
{
}

Bwt::Core::Debug::Exceptions::NoProjectionMatrixException::NoProjectionMatrixException() 
	: std::exception(), message("")
{
}