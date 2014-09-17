#ifndef _COLD_RENDER_RENDER_STATE_H
#define _COLD_RENDER_RENDER_STATE_H

#include <cold/render/impl/gl.h>

namespace cold { namespace render { namespace state {

// A global render state
// <> Self: Class that controls the render state
//          must implement `static void enable()` and `static void disable()`
template <typename Self>
class RenderState {
public:
	RenderState()
		: _initialized(false) { }

	// Enables the render state if value is true, disables otherwise
	void set_enabled(bool value) {
		if (_initialized && _cache == value)
			return;
		_initialized = true;
		_cache = value;
		if (value)
			Self::enable();
		else
			Self::disable();
	}

	// Enables the render state
	void enable() { set_enabled(true); }

	// Disables the render state
	void disable() { set_enabled(false); }

	// Returns whether the state has been enabled
	// def: Default if not changed yet
	bool get_enabled(bool def) { if (_initialized) return _cache; return def; }
private:
	bool _initialized;
	bool _cache;
};
namespace impl {
template <unsigned int Enum>
struct GLBufferState {
	static void enable() { }
	static void disable() { glBindBuffer(Enum, 0); }
};
template <unsigned int Enum>
struct GLFlagState {
	static void enable() { glEnable(Enum); }
	static void disable() { glDisable(Enum); }
};
}

extern RenderState<impl::GLBufferState<GL_ARRAY_BUFFER>> vertex_buffer;
extern RenderState<impl::GLBufferState<GL_ELEMENT_ARRAY_BUFFER>> index_buffer;
extern RenderState<impl::GLFlagState<GL_DEPTH_TEST>> depth_test;
extern RenderState<impl::GLFlagState<GL_CULL_FACE>> backface_culling;

} } }

#endif