#ifndef _COLD_RENDER_ENUMS_H
#define _COLD_RENDER_ENUMS_H

namespace cold {

// Type of a primitive data type
enum DataType {
	// c_byte
	DATA_BYTE				= 0x1400,
	// c_ubyte
	DATA_UNSIGNED_BYTE		= 0x1401,
	// c_short
	DATA_SHORT				= 0x1402,
	// c_ushort
	DATA_UNSIGNED_SHORT		= 0x1403,
	// c_int
	DATA_INT				= 0x1404,
	// c_uint
	DATA_UNSIGNED_INT		= 0x1405,
	// c_float
	DATA_FLOAT				= 0x1406,
	// c_double
	DATA_DOUBLE				= 0x140A,
};

// Mode to draw primitives
enum DrawMode {
	// Draw the vertices as disconnected points
	// A B C D E F
	DRAW_POINTS				= 0x0000,
	// Draw the vertices as disconnected lines
	// A-B C-D E-F
	DRAW_LINES				= 0x0001,
	// Draw the vertices as connected line with end connected to begin
	// A-B-C-D
	// |     |
	// H-G-F-E
	DRAW_LINE_LOOP			= 0x0002,
	// Draw the vertices as connected line with end not connected to begin
	// A-B-C-D
	DRAW_LINE_STRIP			= 0x0003,
	// Draw the vertices as disconnected triangles
	// A--B D
	// | / /|
	// |/ / |
	// C F--E
	DRAW_TRIANGLES			= 0x0004,
	// Draw the vertices as a triangle strip
	// A--C--E--G
	// | /| /| /|
	// |/ |/ |/ |
	// B--D--F--H
	DRAW_TRIANGLE_STRIP		= 0x0005,
	// Draw the vertices as a triangle fan
	// B--A--F
	// | /|\ |
	// |/ | \|
	// C--D--E
	DRAW_TRIANGLE_FAN		= 0x0006,
	// Draw the vertices as disconnected quads
	// A--C E--G
	// |  | |  |
	// |  | |  |
	// B--D F--H
	DRAW_QUADS				= 0x0007,
	// Draws the vertices as a quad strip
	// A--C--E--G
	// |  |  |  |
	// |  |  |  |
	// B--D--F--H
	DRAW_QUAD_STRIP			= 0x0008,
	// Draws the vertices as a solid polygon
	// A-B-C
	// \  /
	//  D-
	DRAW_POLYGON			= 0x0009,
};

// Rasterizer filtering mode
enum TextureFiltering {
	// Nearest-neigbour
	FILTER_NEAREST = 0x2600,
	// Linear interpolation
	FILTER_LINEAR = 0x2601,
};

unsigned int get_data_type_size(DataType t);

}

#endif