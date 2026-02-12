#pragma once

#include <exception>
#include <string>

namespace Bwt
{
	namespace Core
	{
		namespace Debug
		{
			namespace Exception
			{
				class GladInitializeFailException : std::exception
				{
				public:
					std::string message;

					GladInitializeFailException();
					GladInitializeFailException(std::string message);
				};
			}
		}
	}
}