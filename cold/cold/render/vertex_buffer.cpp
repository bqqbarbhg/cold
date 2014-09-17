#include "vertex_buffer.h"
#include <cold/render/vertex_declaration.h>
#include <cold/render/impl/gl.h>
#include <cold/render/vertex_array.h>
#include <cold/util/assert.h>

namespace cold {

VertexBuffer VertexBuffer::Uninitialized;

VertexBuffer::VertexBuffer(const VertexBuffer& b)
	: BaseBuffer(b), vd(0)
{
	COLD_DEBUG_ASSERT(&b == &Uninitialized);
}
VertexBuffer::VertexBuffer(VertexBuffer&& b)
	: BaseBuffer(std::move(b)), vd(b.vd)
{
}
VertexBuffer::VertexBuffer(const VertexDeclaration& vd)
	: BaseBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW), vd(&vd)
{
}
VertexBuffer::VertexBuffer(const VertexArray& va)
	: BaseBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW), vd(&va.get_vertex_declaration())
{
	set_vertices(va);
}

void VertexBuffer::set_vertices(const void *verts, unsigned int count) {
	COLD_DEBUG_ASSERT(vd != 0);
	set_data(verts, count * vd->stride);
}
void VertexBuffer::set_vertices(const VertexArray& arr) {
	set_data(arr.get_data(), arr.get_size());
}

void VertexBuffer::apply() const {
	COLD_DEBUG_ASSERT(vd != 0);
	vd->apply(nullptr);
	BaseBuffer::apply();
}

const VertexDeclaration& VertexBuffer::get_vertex_declaration() const {
	COLD_DEBUG_ASSERT(vd != 0);
	return *vd;
}

void VertexBuffer::operator=(VertexBuffer&& i) {
	BaseBuffer::operator=((BaseBuffer&&)i);
	vd = i.vd;
}


};