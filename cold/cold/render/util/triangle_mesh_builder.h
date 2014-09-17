#ifndef _COLD_RENDER_UTIL_TRIANGLE_MESH_BUILDER_H
#define _COLD_RENDER_UTIL_TRIANGLE_MESH_BUILDER_H

#include <cold/render/util/mesh_builder.h>

namespace cold {

class TriangleMeshBuilder : public MeshBuilder {
public:
	TriangleMeshBuilder(const VertexDeclaration& vd, DataType id);
	template <class T>
	void add_triangle(T t0, T t1, T t2) {
		indices.push_back(vertices.get_count());
		vertices.push_back(t0);
		indices.push_back(vertices.get_count());
		vertices.push_back(t1);
		indices.push_back(vertices.get_count());
		vertices.push_back(t2);	
	}
	template <class T>
	void add_quad(T t0, T t1, T t2, T t3, bool rev=false) {
		unsigned int base = vertices.get_count();
		vertices.push_back(t0);
		vertices.push_back(t1);
		vertices.push_back(t2);
		vertices.push_back(t3);
		
		if (rev) {
			indices.push_back(base);
			indices.push_back(base + 1);
			indices.push_back(base + 2);

			indices.push_back(base + 2);
			indices.push_back(base + 1);
			indices.push_back(base + 3);
		} else {
			indices.push_back(base + 2);
			indices.push_back(base + 1);
			indices.push_back(base);

			indices.push_back(base + 3);
			indices.push_back(base + 1);
			indices.push_back(base + 2);
		}
	}
private:
};

}

#endif