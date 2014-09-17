#ifndef _COLD_ENGINE_WIND_VECTOR_H
#define _COLD_ENGINE_WIND_VECTOR_H

namespace cold {

struct WindVector {
	typedef unsigned char CType;
	inline WindVector(CType r, CType a, CType p)
		: radius(r), azimuth(a), polar(p)
	{
	}
	CType radius, azimuth, polar;
};

}

#endif