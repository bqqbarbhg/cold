#ifndef _COLD_MATH_RAY_H
#define _COLD_MATH_RAY_H

#include <glm/glm.hpp>

namespace cold {

// A 3D ray structure defined as (`origin`, `direction`)
struct Ray {

	// Creates a new uninitialized ray
	Ray() { }

	// Creates a new ray from origin to direction
	Ray(const glm::vec3& origin, const glm::vec3& direction)
		: origin(origin), direction(direction) { }


	// Origin of the ray
	glm::vec3 origin;

	// Direction of the ray (not necessarily normalized)
	glm::vec3 direction;
};

}

#endif