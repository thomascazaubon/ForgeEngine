#include "Assert.h"

#include <iostream>

namespace ForgeEngine
{
#ifdef FORGE_DEBUG_ENABLED
    void Assert(const char* expr_str, bool expr, const char* file, int line, const char* msg)
    {
        if (!expr)
        {
            std::cout << "Assert failed:\t" << msg << "\n"
                << "Expected:\t" << expr_str << "\n"
                << "Source:\t\t" << file << ", line " << line << "\n";

            abort();
        }
    }
#else
    void Assert(const char* expr_str, bool expr, const char* msg)
    {
        if (!expr)
        {
            std::cout << "Assert failed:\t" << msg << "\n"
                << "Expected:\t" << expr_str << "\n";
            abort();
        }
    }
#endif //FORGE_DEBUG_ENABLED
    
}