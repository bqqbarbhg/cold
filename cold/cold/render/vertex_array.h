#ifndef _COLD_RENDER_VERTEX_ARRAY_H
#define _COLD_RENDER_VERTEX_ARRAY_H

#include <cold/render/vertex_declaration.h>

namespace cold {

// An constant-sized array of vertices
class VertexArray {
public:
	VertexArray(const VertexDeclaration& _vd, unsigned int size);
	VertexArray(const VertexArray& va);
	~VertexArray();
	VertexArray& operator=(VertexArray v);

	// Returns a pointer of `T` to the element at `index`
	// index: Index of the element to get
	template <typename T>
	T* get(unsigned int index) const {
		return reinterpret_cast<T*>(_data + index * _vd.stride);
	}

	// Returns a raw pointer to the data
	void *get_data() const { return _data; }

	// Returns the size of the array in bytes
	unsigned int get_size() const { return _size * _vd.stride; }

	// Returns the amount of the vertices in the array
	unsigned int get_count() const { return _size; }

	// Applies the array to the current render state
	void apply() const;

	// Returns the vertex declaration attributed to the array
	const VertexDeclaration& get_vertex_declaration() const { return _vd; }
private:
	unsigned int _size;
	char *_data;
	const VertexDeclaration& _vd;
};

}

#endif