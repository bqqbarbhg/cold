#include "mesh_builder.h"
#include <cold/util/assert.h>
#include <cold/render/mesh.h>

namespace cold {

MeshBuilder::MeshBuilder(const VertexDeclaration& vd, DataType id)
	: vertex_decl(vd)
	, index_type(id)
	, index_size(get_data_type_size(id))
	, vertices(vd.stride)
	, indices(get_data_type_size(id))
{
}

void MeshBuilder::apply(Mesh& mesh) const {
	if (!mesh.is_initialized()) {
		mesh = Mesh(vertex_decl, index_type, DRAW_TRIANGLES);
	} else {
		COLD_DEBUG_ASSERT(mesh.get_vertex_declaration() == vertex_decl);
		COLD_DEBUG_ASSERT(mesh.get_index_type() == index_type);
	}
	mesh.set_vertices(vertices.get_pointer(), vertices.get_count());
	mesh.set_indices(indices.get_pointer(), indices.get_count());
}

}