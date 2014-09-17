#include "blend_state.h"
#include <cold/render/impl/gl.h>
#include <cold/util/assert.h>
#include <cold/render/impl/debug.h>

namespace cold {

unsigned int BlendState::_factor_hash = 0;
const BlendState BlendState::None(_NONE, _NONE);
const BlendState BlendState::Additive(SRC_ALPHA, ONE);
const BlendState BlendState::AlphaBlend(SRC_ALPHA, INV_SRC_ALPHA);
const BlendState BlendState::Opaque(ONE, ZERO);
const BlendState BlendState::Multiply(ZERO, SRC_COLOR);

static const GLenum glemap[] = {
	0,
	GL_NONE,
	GL_ONE,
	GL_SRC_COLOR,
	GL_DST_COLOR,
	GL_ONE_MINUS_SRC_COLOR,
	GL_ONE_MINUS_DST_COLOR,
	GL_SRC_ALPHA,
	GL_DST_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA,
	GL_ONE_MINUS_DST_ALPHA,
};

BlendState::BlendState()
	: source(_NONE), destination(_NONE)
{
	hash = 0;
}

BlendState::BlendState(Factor src, Factor dst)
	: source(src), destination(dst), hash(src << 4 | dst)
{
}

void BlendState::apply() const { COLD_RENDER_DEBUG
	COLD_DEBUG_ASSERT(source != _NONE && destination != _NONE || source == destination);
	if (_factor_hash != hash) {
		if (!_factor_hash) {
			glEnable(GL_BLEND);
			glBlendFunc(glemap[source], glemap[destination]);
		} else if(!hash)
			glDisable(GL_BLEND);
		_factor_hash = hash;
	}
}

}