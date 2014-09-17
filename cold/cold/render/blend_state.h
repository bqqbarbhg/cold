#ifndef _COLD_RENDER_BLEND_STATE_H
#define _COLD_RENDER_BLEND_STATE_H

namespace cold {

// Controls how the renderer blends pixels
struct BlendState {
public:
	// A blending factor applied to either source or destination
	enum Factor {
		_NONE,
		// 0
		ZERO,
		// 1
		ONE,
		// Source color
		SRC_COLOR,
		// Destination color
		DST_COLOR,
		// Inverse source color
		INV_SRC_COLOR,
		// Inverse destination color
		INV_DST_COLOR,
		// Source alpha
		SRC_ALPHA,
		// Destination alpha
		DST_ALPHA,
		// Inverse source alpha
		INV_SRC_ALPHA,
		// Inverse destination alpha
		INV_DST_ALPHA,
	};

	BlendState();
	BlendState(Factor src, Factor dst);

	// Applies the blend state to the current render state
	void apply() const;
	// Returns the source factor
	Factor get_source() const { return source; }
	// Returns the destination factor
	Factor get_destination() const { return destination; }

	const static BlendState None;
	const static BlendState Additive;
	const static BlendState AlphaBlend;
	const static BlendState Opaque;
	const static BlendState Multiply;
private:
	Factor source, destination;
	unsigned int hash;
	static unsigned int _factor_hash;
};

}

#endif