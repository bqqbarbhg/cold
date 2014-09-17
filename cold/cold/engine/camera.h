#ifndef _COLD_ENGINE_CAMERA_H
#define _COLD_ENGINE_CAMERA_H

#include <glm/glm.hpp>

namespace cold {

class Camera {
public:
	glm::mat4 view, projection;
	glm::mat4 view_projection;
	float width, height;
	float get_aspect_ratio() const;
	void update();
};

}

#endif