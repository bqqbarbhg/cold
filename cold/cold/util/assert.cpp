#include "assert.h"
#include <intrin.h>

namespace cold {
	
void _assert(bool expr) {
	if (expr) return;
	__debugbreak();
}

}