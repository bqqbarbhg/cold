#ifndef _COLD_ENGINE_RENDER_CHUNK_H
#define _COLD_ENGINE_RENDER_CHUNK_H

#include <cold/render/mesh.h>

namespace cold {

class Map;
class RenderChunk {
public:
	static const VertexDeclaration& vertex_declaration;
	RenderChunk(int x, int y, int z, int w, int h, int d);

	void update(const Map& map);
	void draw() const;

private:
	const int x, y, z;
	const int w, h, d;
	Mesh static_mesh;
};

}

#endif