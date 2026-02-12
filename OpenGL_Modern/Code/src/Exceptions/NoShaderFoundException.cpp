#include "NoShaderFoundException.h"

Bwt::Core::Debug::Exception::NoShaderFoundException::NoShaderFoundException() : std::exception(), message("")
{
}

Bwt::Core::Debug::Exception::NoShaderFoundException::NoShaderFoundException(std::string message) : std::exception(message.c_str()), message(message)
{
}