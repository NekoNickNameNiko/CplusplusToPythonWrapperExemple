#include "../include/Debug.h"

namespace Bwt
{
	namespace Core
	{
		namespace Debug
		{
			Log::Log() = default;

			Log::~Log()
			{
				if (m_file.is_open())
				{
					m_file.close();
				}
			}

			void Log::OpenFile(std::filesystem::path const& filename)
			{
				m_file.open(filename, std::ios::out);
			}

			void Log::Print(const char* format, ...)
			{
				constexpr size_t BUFFER_SIZE = 1024;
				char buffer[BUFFER_SIZE];

				va_list args;
				va_start(args, format);
				vsnprintf(buffer, BUFFER_SIZE, format, args);
				va_end(args);

				std::cout << buffer;

				if (m_file.is_open())
				{
					m_file << buffer;
					m_file.flush();
				}
			}
		}
	}
}