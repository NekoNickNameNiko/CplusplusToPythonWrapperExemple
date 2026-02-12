#pragma once
#include "CommonInclude.h"
#include <fstream>
#define STRING_CONVERTER(x) #x
#define STRINGIFY(x) STRING_CONVERTER(x)

namespace Bwt
{
    namespace Core
    {
        namespace Debug
        {
            class Log
            {
            public:
                Log();
                ~Log();

                void OpenFile(std::filesystem::path const& filename);
                void Print(const char* format, ...);

            private:
                std::ofstream m_file;
            };

            //Assert macro
            #ifdef _DEBUG
                #define ASSERT(expr) AssertFunction(expr);
            #else 
                #define ASSERT(expr) assert(expr);
            #endif

            inline void AssertFunction(bool expr)
            {
                if (!expr) DebugBreak();
            }

            //Debug_log macro
            #ifdef _DEBUG
                #define DEBUG_LOG(format, ...) do {\
                            Bwt::Core::Debug::Log().Print(__FILE__ "(" STRINGIFY(__LINE__) "): " format "\n", __VA_ARGS__); \
                            OutputDebugStringA(__FILE__ "(" STRINGIFY(__LINE__) "): "); \
                            char buffer[1024]; \
                            snprintf(buffer, 1024, format, __VA_ARGS__); \
                            OutputDebugStringA(buffer); \
                            OutputDebugStringA("\n"); \
                    } while (0)
            #else
                 #define DEBUG_LOG(format, ...) ((void)0)
            #endif 

        }
    }
}
