#ifndef _COLD_INPUT_INPUT_H
#define _COLD_INPUT_INPUT_H

namespace cold {

// Input source
// <T>: The type of the input
template <typename T>
class Input {
public:
	virtual ~Input() { }

	// Gets the current input from the source
	// May update state or be expensive, so you should cache
	// the result if you are going to call it multiple times
	virtual T get() const = 0;
};

}

#endif