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

				class NoShaderFoundException : std::exception
				{

				public:

					std::string message;

					NoShaderFoundException();
					NoShaderFoundException(std::string message);

				};

			}
		}
	}
}