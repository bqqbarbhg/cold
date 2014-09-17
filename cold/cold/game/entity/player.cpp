#include "player.h"

#include <glm/ext.hpp>
#include <cold/engine/scene.h>
#include <cold/input/arrow_input.h>
#include <cold/input/mouse_input.h>
#include <cold/input/key_input.h>
#include <cold/input/multiplier_input.h>

namespace cold {

EntityPlayer::EntityPlayer(glm::vec3 p)
	: EntityPhysical(p, glm::vec3(0.8f, 1.9f, 0.8f)), pitch(0.0f), yaw(0.0f)
{
	Mouse::lock();
	Mouse::set_visible(false);
	move_bind += new ArrowInput(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
	aim_bind += new MultiplierInput<glm::vec2>(new ArrowInput(SDLK_DOWN, SDLK_UP, SDLK_LEFT, SDLK_RIGHT), glm::vec2(0.05f));
	aim_bind += new MultiplierInput<glm::vec2>(new MouseInput(), glm::vec2(0.1f));
	jump_bind += new KeyInput(KeyInput::PRESSED, SDLK_SPACE);
	friction_ground = glm::vec3(15.0f, 0.0f, 15.0f);
	friction_air = glm::vec3(10.0f, 0.0f, 10.0f);
}

void EntityPlayer::update(float elapsed) {
	glm::vec2 a = aim_bind.get();
	yaw -= a.x;
	pitch += a.y;

	glm::vec3 lookDir = glm::rotateY(glm::rotateX(glm::vec3(0.0f, 0.0f, 1.0f), pitch), yaw);
	glm::vec3 flatLook = lookDir;
	flatLook.y = 0.0f;
	flatLook = glm::normalize(flatLook);

	glm::vec2 v = move_bind.get();
	float f = glm::length(v);
	if (f) {
		v /= f;
		vel += (v.y * flatLook + v.x * glm::cross(flatLook, glm::vec3(0.0f, 1.0f, 0.0f))) * elapsed * 100.0f;
	}

	if (jump_bind.get() && on_ground) {
		vel.y += 4.0f;
	}

	glm::vec3 eye = get_center() + glm::vec3(0.0f, 0.8f, 0.0f);
	glm::vec3 trg = eye + lookDir;
	scene->camera.view = glm::lookAt(eye, trg, glm::vec3(0.0f, 1.0f, 0.0f));
	scene->camera.projection = glm::perspective(90.0f, scene->camera.get_aspect_ratio(), 0.05f, 1000.0f);

	EntityPhysical::update(elapsed);
}

void EntityPlayer::draw() {
}

}