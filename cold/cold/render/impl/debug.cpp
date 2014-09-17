#include "debug.h"
#include <cold/render/render.h>

namespace cold { namespace impl {

void RenderDebugHandle::check_error() const {
	render::error_t err;
	if (render::get_error(err)) {
		std::string s = render::get_error_string(err);
		__debugbreak();
	}
}

} }