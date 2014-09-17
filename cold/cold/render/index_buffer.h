#ifndef _COLD_RENDER_INDEX_BUFFER_H
#define _COLD_RENDER_INDEX_BUFFER_H

#include <cold/render/impl/base_buffer.h>
#include <cold/render/enums.h>

namespace cold {

// Buffer of indices in video memory
// Non-copyable except from IndexBuffer::Uninitialized
class IndexBuffer : public impl::BaseBuffer {
public:
	IndexBuffer(const IndexBuffer& i);
	IndexBuffer(IndexBuffer&& i);
	IndexBuffer(DataType i);
	void operator= (IndexBuffer&& i);

	// Draws the index buffer
	// The index buffer must be applied before calling this
	// A vertex buffer or a vertex pointer must be applied before calling this
	// mode: Mode to draw the vertices
	// count: Count of _indices_ (not primitives) to draw
	// begin: Index of the first index to begin drawing from
	void draw(DrawMode mode, unsigned int count, unsigned int begin=0) const;

	// Sets the indices for the buffer
	// indices: Array of `count` indices
	// count: Amount of indices to copy to the buffer
	void set_indices(const void* indices, unsigned int count);

	// Returns the index type attributed with the buffer
	DataType get_index_type() const { return index_type; }

	// Applies the index buffer to the current render state
	void apply() const;

	static IndexBuffer Uninitialized;
private:
	IndexBuffer() { }
	DataType index_type;
};

}

#endif