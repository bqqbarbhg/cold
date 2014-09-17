#ifndef _COLD_RENDER_RENDER_H
#define _COLD_RENDER_RENDER_H

#include <glm/glm.hpp>
#include <string>
#include <cold/render/enums.h>

namespace cold { namespace render {

// Number of draw calls in the current frame
extern unsigned int draw_calls;

// Rendering error code
typedef unsigned int error_t;

// Clears the backbuffer with the color
// color: Color to clear the backbuffer with
void clear(const glm::vec4& color);

// Clears the backbuffer with the color and a depth
// color: Color to clear the backbuffer with
// depth: Color to clear the depth buffer with
void clear(const glm::vec4& color, float depth);

// Gets the current error status
// May be very expensive to call, should be only called in debug mode
// err (out): error_t to write the error code to
// returns: true if an error occoured since the last call to `get_error`
bool get_error(error_t& err);

// Returns a string describing the render error
// err: Error code to get the description of
std::string get_error_string(const error_t& err);

// Updates the back buffer
// Should be called in the end of the rendering routine
void update();

void draw(DrawMode mode, unsigned int count, DataType index_type, const void *indices, unsigned int begin=0);

#ifdef _DEBUG
// Should be called only on native render operations (below cold:: level of abstraction) eg. pure GL calls
#define COLD_INCREASE_DRAW_CALLS() ::cold::render::draw_calls++;
#else
// Should be called only on native render operations (below cold:: level of abstraction) eg. pure GL calls
#define COLD_INCREASE_DRAW_CALLS() ::cold::render::draw_calls++;
#endif

} }

#endif