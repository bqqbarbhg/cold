#include "chunk.h"
#include <cold/engine/map.h>
#include <cold/render/util/basic_vertex_types.h>
#include <cold/render/util/basic_vertex_declarations.h>
#include <cold/render/util/triangle_mesh_builder.h>

namespace cold {

const VertexDeclaration& RenderChunk::vertex_declaration = VertexPositionColor;

RenderChunk::RenderChunk(int x, int y, int z, int w, int h, int d)
	: x(x), y(y), z(z), w(w), h(h), d(d)
	, static_mesh(vertex_declaration, DATA_UNSIGNED_INT)
{
}
void RenderChunk::draw() const {
	static_mesh.draw();
}
namespace {
	void addq(TriangleMeshBuilder& tmb, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 o, bool r) {
		tmb.add_quad(
			VTPositionColor(a, o),
			VTPositionColor(b, o),
			VTPositionColor(c, o),
			VTPositionColor(d, o),
			r);
	}
}
void RenderChunk::update(const Map& map) {
	TriangleMeshBuilder tmb(
		static_mesh.get_vertex_declaration(),
		static_mesh.get_index_type());
	
	for (int i = x; i < x + w; i++) {
		for (int j = y; j < y + h; j++) {
			for (int k = z; k < z + d; k++) {
				if (map.get_block_const(i, j, k)->is_solid()) {
					glm::vec3 v0(i, j, k), v1(i+1, j, k), v2(i, j+1, k), v3(i+1, j+1, k),
							v4(i, j, k+1), v5(i+1, j, k+1), v6(i, j+1, k+1), v7(i+1, j+1, k+1);

					if (i > 0 && !map.get_block_const(i - 1, j, k)->is_solid())
						addq(tmb, v0, v4, v2, v6, glm::vec3(1.0f, 0.0f, 0.0f), true);
					if (j > 0 && !map.get_block_const(i, j - 1, k)->is_solid())
						addq(tmb, v0, v1, v4, v5, glm::vec3(0.0f, 1.0f, 0.0f), true);
					if (k > 0 && !map.get_block_const(i, j, k - 1)->is_solid())
						addq(tmb, v0, v1, v2, v3, glm::vec3(0.0f, 0.0f, 1.0f), false);
					if (i < map.width - 1 && !map.get_block_const(i + 1, j, k)->is_solid())
						addq(tmb, v1, v5, v3, v7, glm::vec3(1.0f, 0.0f, 1.0f), false);
					if (j < map.height - 1 && !map.get_block_const(i, j + 1, k)->is_solid())
						addq(tmb, v2, v3, v6, v7, glm::vec3(1.0f, 1.0f, 0.0f), false);
					if (k < map.depth - 1 && !map.get_block_const(i, j, k + 1)->is_solid())
						addq(tmb, v4, v5, v6, v7, glm::vec3(0.0f, 1.0f, 1.0f), true);
				}
			}
		}
	}

	tmb.apply(static_mesh);
}

}