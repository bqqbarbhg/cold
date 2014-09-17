#include "render_state.h"

namespace cold { namespace render { namespace state {

RenderState<impl::GLBufferState<GL_ARRAY_BUFFER>> vertex_buffer;
RenderState<impl::GLBufferState<GL_ELEMENT_ARRAY_BUFFER>> index_buffer;
RenderState<impl::GLFlagState<GL_DEPTH_TEST>> depth_test;
RenderState<impl::GLFlagState<GL_CULL_FACE>> backface_culling;

} } }