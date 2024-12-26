#pragma once

namespace ForgeEngine
{
#ifdef FORGE_DEBUG_ENABLED
#define ASSERT(Expr, Msg) \
    Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#define ASSERT(Expr, Msg) \
    Assert(#Expr, Expr, Msg)
#endif
    //TODO: Hide
#ifdef FORGE_DEBUG_ENABLED
    void Assert(const char* expr_str, bool expr, const char* file, int line, const char* msg);
#else
    void Assert(const char* expr_str, bool expr, const char* msg);
#endif //FORGE_DEBUG_ENABLED
}
