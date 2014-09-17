#ifndef _COLD_RENDER_MESH_H
#define _COLD_RENDER_MESH_H

#include <cold/render/enums.h>
#include <cold/render/vertex_buffer.h>
#include <cold/render/index_buffer.h>

namespace cold {

class VertexDeclaration;

// Container of a VertexBuffer and IndexBuffer and some drawing information
class Mesh {
public:

	// Creates a new uninitialized mesh instance
	Mesh();

	// Creates a new mesh instance
	// vertDecl: Vertex declaration of the vertices
	// indexType: Data type of the indices (DATA_UNSIGNED_BYTE, DATA_UNSIGNED_USHORT, DATA_UNSIGNED_INT)
	// drawMode: Rendering mode of the mesh
	Mesh(const VertexDeclaration &vertDecl, DataType indexType, DrawMode drawMode=DRAW_TRIANGLES);

	Mesh(Mesh&& m);

	Mesh& operator= (Mesh&& m);

	// Draws the mesh
	void draw() const;

	// Rendering mode of the mesh
	DrawMode draw_mode;

	// Returns the amount of indices in the mesh
	unsigned int get_index_count() const { return index_count; }

	// Sets the indices of the mesh
	// indices: Array of `count` indices of the type attributed with the mesh
	// count: Amount of indices to copy to the buffer
	void set_indices(const void* indices, unsigned int count);

	// Sets the vertices of the mesh
	// vertices: Array of `count` vertices of the vertex declaration attributed with the mesh
	// count: Amount of vertices to copy to the buffer
	void set_vertices(const void* vertices, unsigned int count);

	// Returns the data type of the indices
	DataType get_index_type() const { return index_buffer.get_index_type(); }

	// Returns the vertex declaration of the vertices
	const VertexDeclaration& get_vertex_declaration() const { return vertex_buffer.get_vertex_declaration(); }

	// Returns whether the mesh is initialized
	bool is_initialized() const { return initialized; }

private:
	Mesh(const Mesh& m);
	Mesh& operator=(const Mesh& m);

	bool initialized;
	VertexBuffer vertex_buffer;
	IndexBuffer index_buffer;
	unsigned int index_count;
};

}

#endif