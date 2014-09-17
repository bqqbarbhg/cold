#ifndef _COLD_RENDER_VERTEX_BUFFER_H
#define _COLD_RENDER_VERTEX_BUFFER_H

#include <cold/render/impl/base_buffer.h>

namespace cold {

class VertexDeclaration;
class VertexArray;

// Buffer of vertices in video memory
// Non-copyable except from VertexBuffer::Uninitialized
class VertexBuffer : public impl::BaseBuffer {
public:
	VertexBuffer(const VertexBuffer& b);
	VertexBuffer(VertexBuffer&& b);
	explicit VertexBuffer(const VertexDeclaration& vd);
	explicit VertexBuffer(const VertexArray& va);
	void operator=(VertexBuffer&& b);

	// Sets the vertices for the buffer
	// vertices: Array of `count` vertices
	// count: Amount of vertices to copy to the buffer
	void set_vertices(const void *vertices, unsigned int count);

	// Sets the vertices for the buffer
	// arr: Vertex array with the same vertex declaration as the buffer
	void set_vertices(const VertexArray& arr);

	// Applies the buffer to the current render state
	void apply() const;	

	// Gets the vertex declaration attributed with the buffer
	const VertexDeclaration& get_vertex_declaration() const;

	static VertexBuffer Uninitialized;
private:
	VertexBuffer() { }
	const VertexDeclaration* vd;
};

}

#endif