#include "vertex_declaration.h"
#include <cold/render/vertex_element.h>
#include <cold/render/impl/gl.h>
#include <cold/render/impl/debug.h>
#include <cold/render/render_state.h>

namespace cold {

static unsigned int ve_sum(const VertexElement* ptr) {
	unsigned int i = 0;
	for (; ptr->type; ptr++) {
		i += ptr->size;
	}
	return i;
}

VertexDeclaration::VertexDeclaration(const VertexElement* ptr)
	: elements(ptr), stride(ve_sum(ptr))
{
}

bool VertexDeclaration::operator==(const VertexDeclaration& rhs) const {
	if (stride != rhs.stride)
		return false;
	const VertexElement *p, *o;
	for (p = elements, o = rhs.elements; p->type && o->type; p++, o++) {
		if (p->type != o->type) return false;
		if (p->component_type != o->component_type) return false;
		if (p->size != o->size) return false;
		if (p->type != o->type) return false;
	}
	return !(p->type || o->type);
}
bool VertexDeclaration::operator!=(const VertexDeclaration& rhs) const {
	return !(*this == rhs);
}

void VertexDeclaration::apply(const void* ptr) const { COLD_RENDER_DEBUG
	const char* c = reinterpret_cast<const char*>(ptr);
	render::state::vertex_buffer.set_enabled(ptr == nullptr);
	for (const VertexElement* p = elements; p->type; p++) {
		switch (p->type) {
		case VertexElement::POSITION:
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(p->count, p->component_type, stride, c);
			break;
		case VertexElement::TEXTURE_COORDINATE:
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(p->count, p->component_type, stride, c);
			break;
		case VertexElement::NORMAL:
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(p->component_type, stride, c);
			break;
		case VertexElement::COLOR:
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(p->count, p->component_type, stride, c);
			break;
		}
		c += p->size;
	}
}

}