#include "keyboard.h"
#include <cold/util/assert.h>

namespace cold {

bool Keyboard::_state[KEY_COUNT];
bool Keyboard::reading = false;
unsigned int Keyboard::_time[KEY_COUNT];
unsigned int Keyboard::_counter = 0;
std::queue<st_char> Keyboard::read_queue;

void Keyboard::initialize() {
	for (int i = 0; i != KEY_COUNT; i++) {
		_state[i] = false;
		_time[i] = 0;
	}
}

void Keyboard::begin_read(int delay, int freq) {
	COLD_ASSERT(!reading);
	reading = true;
	SDL_EnableUNICODE(1);
	SDL_EnableKeyRepeat(delay, freq);
}
void Keyboard::write(st_char c) {
	COLD_DEBUG_ASSERT(reading);
	read_queue.push(c);
}
st_char Keyboard::read() {
	COLD_DEBUG_ASSERT(reading);
	if (read_queue.empty()) return 0;
	st_char c = read_queue.back();
	read_queue.pop();
	return c;
}
void Keyboard::end_read() {
	COLD_ASSERT(reading);
	reading = false;
	SDL_EnableUNICODE(0);
	SDL_EnableKeyRepeat(0, 0);
}

}