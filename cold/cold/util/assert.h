#ifndef _COLD_UTIL_ASSERT_H
#define _COLD_UTIL_ASSERT_H

namespace cold {

void _assert(bool expr);
#define COLD_ASSERT(expr) ::cold::_assert(expr)
#ifdef _DEBUG
#define COLD_DEBUG_ASSERT(expr) COLD_ASSERT(expr)
#define COLD_SLOW_DEBUG_ASSERT(expr) COLD_ASSERT(expr)
#else
#define COLD_DEBUG_ASSERT(expr) 
#define COLD_SLOW_DEBUG_ASSERT(expr)
#endif

}

#endif