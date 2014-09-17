#include "basic_vertex_declarations.h"
#include <cold/render/vertex_element.h>
#include <cold/render/types.h>

namespace cold {

#define VERT_DECL(name) \
	extern const VertexElement name##_elements[]; \
	const VertexDeclaration name(name##_elements); \
	const VertexElement name##_elements[] \

	VERT_DECL(VertexPosition) = {
		{ VertexElement::POSITION, DATA_FLOAT, 3, 3 * sizeof(c_float) },
		{ VertexElement::END },
	};
	VERT_DECL(VertexPositionColor) = {
		{ VertexElement::POSITION, DATA_FLOAT, 3, 3 * sizeof(c_float) },
		{ VertexElement::COLOR, DATA_FLOAT, 3, 3 * sizeof(c_float) },
		{ VertexElement::END },
	};
	VERT_DECL(VertexPositionTexture) = {
		{ VertexElement::POSITION, DATA_FLOAT, 3, 3 * sizeof(c_float) },
		{ VertexElement::TEXTURE_COORDINATE, DATA_FLOAT, 2, 2 * sizeof(c_float) },
		{ VertexElement::END },
	};
	VERT_DECL(VertexPositionColorTexture) = {
		{ VertexElement::POSITION, DATA_FLOAT, 3, 3 * sizeof(c_float) },
		{ VertexElement::COLOR, DATA_FLOAT, 3, 3 * sizeof(c_float) },
		{ VertexElement::TEXTURE_COORDINATE, DATA_FLOAT, 2, 2 * sizeof(c_float) },
		{ VertexElement::END },
	};

}