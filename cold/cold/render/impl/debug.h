#ifndef _COLD_RENDER_DEBUG_H
#define _COLD_RENDER_DEBUG_H

namespace cold { namespace impl {

class RenderDebugHandle {
public:
	RenderDebugHandle() { check_error(); }
	~RenderDebugHandle() { check_error(); }
	void check_error() const;
};

#ifdef COLD_DEBUG_RENDERING
 #define COLD_RENDER_DEBUG ::cold::impl::RenderDebugHandle _cold_rdh;
 #define COLD_RENDER_CHECK _cold_rdh.check_error();
#else
 #define COLD_RENDER_DEBUG
 #define COLD_RENDER_CHECK
#endif

} }

#endif