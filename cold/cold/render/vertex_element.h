#ifndef _COLD_RENDER_VERTEX_ELEMENT
#define _COLD_RENDER_VERTEX_ELEMENT

#include <cold/render/enums.h>

namespace cold {

// Describes a part of a vertex
struct VertexElement {
public:
	enum Type {
		// Terminating vertex element
		END = 0,
		// Vertex position
		POSITION,
		// Texture coordinate
		TEXTURE_COORDINATE,
		// Vertex normal
		NORMAL,
		// Vertex color
		COLOR,
	};

	// Type of the vertex element
	Type type;
	// Type of the vertex components
	DataType component_type;
	// Amount of components in the element
	unsigned int count;
	// Size of the element in bytes
	unsigned int size;
};

}

#endif