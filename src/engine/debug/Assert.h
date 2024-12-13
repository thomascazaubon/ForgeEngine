#pragma once

namespace ForgeEngine
{

#ifdef FORGE_DEBUG_ENABLED
#   define ASSERT(Expr, Msg) \
    Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define Assert(Expr, Msg) ;
#endif
	//TODO: Hide
	void Assert(const char* expr_str, bool expr, const char* file, int line, const char* msg);
}
