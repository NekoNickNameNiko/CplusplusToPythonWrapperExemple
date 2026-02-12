#include "GladInitializeFailException.h"

Bwt::Core::Debug::Exception::GladInitializeFailException::GladInitializeFailException() 
	: std::exception(), message("")
{}

Bwt::Core::Debug::Exception::GladInitializeFailException::GladInitializeFailException(std::string msg)
	: std::exception(msg.c_str()), message(msg)
{}