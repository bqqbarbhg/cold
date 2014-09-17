#include "render.h"
#include <cold/render/impl/gl.h>
#include <cold/render/render_state.h>

namespace cold { namespace render {

unsigned int draw_calls;
void clear(const glm::vec4& color) {
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void clear(const glm::vec4& color, float depth) {
	glClearColor(color.x, color.y, color.z, color.w);
	glClearDepth(depth);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool get_error(error_t& err) {
	return (err = glGetError()) != GL_NO_ERROR;
}
std::string get_error_string(const error_t& err) {
	return (const char*)gluErrorString(err);
}
void update() {
	SDL_GL_SwapBuffers();
	draw_calls = 0;
}
void draw(DrawMode mode, unsigned int count, DataType index_type, const void* indices, unsigned int begin) {
	if (count == 0) return;
	COLD_INCREASE_DRAW_CALLS();
	render::state::index_buffer.set_enabled(indices == nullptr);
	glDrawElements(mode, count, index_type, (void*)(get_data_type_size(index_type) * begin + (size_t)indices));
}

} }