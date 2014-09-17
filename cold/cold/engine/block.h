#ifndef _COLD_ENGINE_BLOCK_H
#define _COLD_ENGINE_BLOCK_H

#include <cold/engine/wind_vector.h>

namespace cold {

struct Block {
public:
	typedef unsigned char ptr_t;
	typedef unsigned char half_t;
	
	static const int size = 3;

	inline bool is_solid() const {
		return (*cptr & 0x80) != 0;
	}
	inline void set_solid(unsigned int id) {
		*cptr &= ~0x80;
		*cptr |= 0x80 | id;
	}
	inline void set_air() {
		*cptr = 0;
	}

	//	Air functions
	//		Getters
	inline WindVector get_air_wind() const {
		return WindVector(cptr[1] >> 4, cptr[1] & 0xF, cptr[2] & 0xF);
	}
	inline half_t get_air_pressure() const {
		return cptr[0] >> 4;
	}
	inline half_t get_air_light() const {
		return cptr[0] & 0x0F;
	}
	inline half_t get_air_snow() const {
		return cptr[2] >> 4;
	}
	//		Setters
	inline void set_air_wind(const WindVector& v) {
		cptr[1] = v.radius | v.azimuth;
		cptr[2] &= 0xF;
		cptr[2] |= v.polar;
	}
	inline void set_air_pressure(half_t v) {
		cptr[0] &= 0x70;
		cptr[0] = (v & 0x7) << 4;
	}
	inline void set_air_light(half_t v) {
		cptr[0] &= 0x0F;
		cptr[0] |= v;
	}
	inline void set_air_snow(half_t v) {
		cptr[2] &= 0xF0;
		cptr[2] = v << 4;
	}

	//	Solid functions
	//		Getters
	inline half_t get_solid_id() const {
		return cptr[0] & 0x7F;
	}
	inline half_t get_solid_meta() const {
		return cptr[1];
	}
	inline half_t get_solid_ao() const {
		return cptr[2] >> 4;
	}
	inline half_t get_solid_snow() const {
		return cptr[2] & 0xF;
	}

	//		Setters
	inline void set_solid_id(half_t id) {
		cptr[0] = id | 0x80;
	}
	inline void set_solid_meta(half_t v) {
		cptr[1] = v;
	}
	inline void set_solid_ao(half_t v) {
		cptr[2] &= 0xF0;
		cptr[2] |= v << 4;
	}
	inline void set_solid_snow(half_t v) {
		cptr[2] &= 0xF;
		cptr[2] |= v;
	}

private:
	ptr_t cptr[3];
};

}

#endif