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
				class CompileShaderFailException : std::exception
				{
				public:

					std::string message;

					CompileShaderFailException();
					CompileShaderFailException(std::string msg);

				};
			}
		}
	}
}