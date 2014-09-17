#ifndef _COLD_RENDER_VERTEX_DECLARATION_H
#define _COLD_RENDER_VERTEX_DECLARATION_H

#include <vector>

namespace cold {

struct VertexElement;

// Describes one vertex in a buffer
class VertexDeclaration {
public:
	VertexDeclaration(const VertexElement* ptr);
	bool operator==(const VertexDeclaration& rhs) const;
	bool operator!=(const VertexDeclaration& rhs) const;

	// Applies the vertex declaration to vertices
	// ptr: Source of the vertices (pointer to vertices or 0 for vertex buffer)
	void apply(const void* ptr) const;

	// Pointer to elements describing a vertex
	const VertexElement* elements;

	// Size of a vertex in bytes
	const unsigned int stride;
};

}

#endif