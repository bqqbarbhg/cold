#ifndef _COLD_INPUT_KEYBOARD_H
#define _COLD_INPUT_KEYBOARD_H

#include <cold/input/io.h>
#include <cold/util/string.h>
#include <queue>

namespace cold {
	class Keyboard {
	public:
		// Number of supported keys in a keyboard
		const static unsigned int KEY_COUNT = 322;

		// Gets whther a key is held down currently
		static bool down(SDLKey key) {
			return _state[key];
		}

		// Gets whether a key relased currently
		static bool up(SDLKey key) {
			return !_state[key];
		}

		// Gets whether a key has just been pressed
		static bool pressed(SDLKey key) {
			return _state[key] && _time[key] == _counter;
		}

		// Gets whether a key has just been released
		static bool released(SDLKey key) {
			return !_state[key] && _time[key] == _counter;
		}

		// Begins reading from the keyboard
		// repeat: Time the user has to hold a key to repeat it
		// freq: Frequency of the repeating
		static void begin_read(int repeat=0, int freq=0);

		// Reads an unicode character from the keyboard
		// may return multiple values in one frame
		// Returns 0 if there are no more characters to read
		// `begin_read` must be called before starting to read
		// from the keyboard
		static st_char read();

		// Ends reading from keyboard
		static void end_read();

		// Returns whether the keyboard is currently reading
		// unicode characters from the keyboard
		static bool is_reading() { return reading; }

		// Initializes the keyboard
		// ! Internal (cold/platform/application)
		static void initialize();

		// Updates the keyboard
		// ! Internal (cold/platform/application)
		static void update() {
			_counter++;
		}

		// Sets a key pressed
		// ! Internal (cold/platform/application)
		static void set_key(SDLKey key, bool value) {
			_state[key] = value;
			_time[key] = _counter;
		}

		// Writes a keypress to the buffer
		// ! Internal (cold/platform/application)
		static void write(st_char c);
	private:
		static bool _state[KEY_COUNT];
		static unsigned int _time[KEY_COUNT];
		static unsigned int _counter;
		static bool reading;
		static std::queue<st_char> read_queue;
	};
};

#endif