#include "WindowCreationFailException.h"

Bwt::Core::Debug::Exception::WindowCreationFailException::WindowCreationFailException()
{
}

Bwt::Core::Debug::Exception::WindowCreationFailException::WindowCreationFailException(std::string msg)
	: std::exception(msg.c_str()), message(msg)
{
}
