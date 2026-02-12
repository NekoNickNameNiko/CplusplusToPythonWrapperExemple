#pragma once

#include <exception>
#include <string>

namespace Bwt
{
	namespace Core
	{
		namespace Debug
		{
			namespace Exceptions
			{
				class NoProjectionMatrixException : std::exception
				{
				public:

					std::string message;
 
					NoProjectionMatrixException();
					NoProjectionMatrixException(std::string msg);

				};
			}
		}
	}
}