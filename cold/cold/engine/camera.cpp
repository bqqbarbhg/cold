#include "camera.h"

namespace cold {

float Camera::get_aspect_ratio() const {
	return width / height;
}

void Camera::update() {
	view_projection = projection * view;
}

}