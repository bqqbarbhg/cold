#include "mesh.h"
#include <cold/util/assert.h>
#include <utility>

namespace cold {

Mesh::Mesh()
	: vertex_buffer(VertexBuffer::Uninitialized)
	, index_buffer(IndexBuffer::Uninitialized)
	, initialized(false)
{
}

Mesh::Mesh(const VertexDeclaration& vd, DataType id, DrawMode dm)
	: vertex_buffer(vd)
	, index_buffer(id)
	, draw_mode(dm)
	, index_count(0)
{
}
void Mesh::draw() const {
	if (index_count > 0) {

		vertex_buffer.apply();
		index_buffer.apply();
		index_buffer.draw(draw_mode, index_count);
	}
}

Mesh::Mesh(Mesh&& m)
	: vertex_buffer(std::move(m.vertex_buffer))
	, index_buffer(std::move(m.index_buffer))
	, index_count(m.index_count)
	, initialized(m.initialized)
	, draw_mode(m.draw_mode)
{
}

Mesh& Mesh::operator=(Mesh&& m) {
	vertex_buffer = std::move(m.vertex_buffer);
	index_buffer = std::move(m.index_buffer);
	index_count = m.index_count;
	initialized = m.initialized;
	draw_mode = m.draw_mode;
	return *this;
}

void Mesh::set_indices(const void* indices, unsigned int count) {
	index_buffer.set_indices(indices, count);
	index_count = count;
}

void Mesh::set_vertices(const void* vertices, unsigned int count) {
	vertex_buffer.set_vertices(vertices, count);
}

}