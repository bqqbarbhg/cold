#ifndef _COLD_INPUT_KEY_INPUT_H
#define _COLD_INPUT_KEY_INPUT_H

#include <cold/input/input.h>
#include <cold/input/keyboard.h>

namespace cold {

// Returns input from one key
class KeyInput : public Input<bool> {
public:
	// Trigger type of the input
	enum Type {
		// Every frame when pressed
		DOWN,
		// Every frme when released
		UP,
		// The frame when the button was pressed
		PRESSED,
		// The frame when the button was released
		RELEASED,
	};
	// t: Input action to listen to
	// k: Key to listen to
	KeyInput (Type t, SDLKey k)
		: type(t), key(k)
	{
	}

	bool get() const {
		switch (type) {
		case DOWN: return Keyboard::down(key);
		case UP: return Keyboard::up(key);
		case PRESSED: return Keyboard::pressed(key);
		case RELEASED: return Keyboard::released(key);
		}
		return false;
	}

private:
	Type type;
	SDLKey key;
};

}

#endif