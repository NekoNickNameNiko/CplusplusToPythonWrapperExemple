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
				class WindowCreationFailException : std::exception
				{
				public:

					std::string message;

					WindowCreationFailException();
					WindowCreationFailException(std::string message);

				};
			}
		}
	}
}