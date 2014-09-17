#include "index_buffer.h"
#include <cold/render/impl/gl.h>
#include <cold/util/assert.h>
#include <cold/render/render.h>
#include <cold/render/render_state.h>
#include <utility>

namespace cold {

IndexBuffer IndexBuffer::Uninitialized;

IndexBuffer::IndexBuffer(const IndexBuffer& i)
	: BaseBuffer(i)
{
	COLD_DEBUG_ASSERT(&i == &Uninitialized);
}
IndexBuffer::IndexBuffer(IndexBuffer&& i)
	: BaseBuffer(std::move(i)), index_type(i.index_type)
{
}

IndexBuffer::IndexBuffer(DataType i)
	: BaseBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW), index_type(i)
{
}

void IndexBuffer::draw(DrawMode mode, unsigned int count, unsigned int begin) const {
	render::draw(mode, count, index_type, nullptr, begin);
}

void IndexBuffer::set_indices(const void* data, unsigned int count) {
	set_data(data, count * get_data_type_size(index_type));
}

void IndexBuffer::apply() const {
	COLD_DEBUG_ASSERT(index_type == DATA_UNSIGNED_BYTE || index_type == DATA_UNSIGNED_SHORT || index_type == DATA_UNSIGNED_INT);
	render::state::index_buffer.enable();
	BaseBuffer::apply();
}

void IndexBuffer::operator=(IndexBuffer&& i) {
	BaseBuffer::operator=((BaseBuffer&&)i);
	index_type = i.index_type;
}

}