#ifndef _COLD_RENDER_UTIL_MESH_BUIILDER_H
#define _COLD_RENDER_UTIL_MESH_BUIILDER_H

#include <cold/render/enums.h>
#include <cold/util/buffer_vector.h>
#include <cold/render/vertex_declaration.h>

namespace cold {

class VertexDeclaration;
class Mesh;

// Utility to build meshes
class MeshBuilder {
public:
	MeshBuilder(const VertexDeclaration& vd, DataType id);
	virtual ~MeshBuilder() { }

	// Applies the built vertices and indices to a mesh
	void apply(Mesh& mesh) const;

	BufferVector vertices;
	BufferVector indices;
private:
	const VertexDeclaration& vertex_decl;
	unsigned int index_size;
	DataType index_type;
};

}

#endif