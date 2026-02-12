#include "CompileShaderFailException.h"

#include <string>

Bwt::Core::Debug::Exception::CompileShaderFailException::CompileShaderFailException() 
	: std::exception(), message()
{
}

Bwt::Core::Debug::Exception::CompileShaderFailException::CompileShaderFailException(std::string msg) 
	: std::exception(msg.c_str()), message(msg)
{
}
