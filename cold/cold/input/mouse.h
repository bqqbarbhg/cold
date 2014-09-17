#ifndef _COLD_INPUT_MOUSE_H
#define _COLD_INPUT_MOUSE_H

#include <glm/glm.hpp>

namespace cold {

class Mouse {
public:
	// Index of the left mouse button
	static const int LEFT = 1;
	
	// Index of the middle mouse button (scroll wheel)
	static const int MIDDLE = 2;

	// Index of the right mouse button
	static const int RIGHT = 3;
	
	// Returns the position of the cursor relative to the current window
	static glm::vec2 get_position() {
		return pos;
	}

	// Gets whether a button is pressed
	static bool get_button(int button);
	
	// Sets the position where the mouse is locked
	// Must be re-called if the window is resized
	// x: X-coordinate from the top-left of the window
	// y: Y-coorinate from the top-left of the window
	static void set_lock_position(int x, int y);

	// Sets whether the mouse input is active, when the mouse is locked but inactive
	// the curstor won't be warped to the lock position
	static void set_active(bool active);

	// Locks the mouse (lock position can be set using set_lock_position)
	// it defaults to the center of the screen
	static void lock();

	// Unlocks the mouse
	static void unlock();

	// Sets whether the default cursor is visible
	static void set_visible(bool visible);

	// Updates the mouse
	// ! Internal (cold/platform/application)
	static void update();
private:
	static void _update_position();
	static glm::vec2 pos;
	static unsigned int buttons;
	static int center_x, center_y;
	static bool lock_updated;
	static bool locked;
	static bool active;
};

}

#endif