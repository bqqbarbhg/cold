#ifndef _COLD_INPUT_MULTIPLIER_INPUT_H
#define _COLD_INPUT_MULTIPLIER_INPUT_H

#include <cold/input/input.h>
#include <cold/util/unique_ptr.h>

namespace cold {

// Multiplies the source input with a constant
// <T>: Type of the input
template <typename T>
class MultiplierInput : public Input<T> {
public:
	// src: The inner input source
	// v: Factor to multiply the input with
	MultiplierInput(Input<T>* src, const T& v)
		: source(src), multiplier(v)
	{
	}

	T get() const {
		return source->get() * multiplier;
	}

	UniquePtr<Input<T>> source;
	T multiplier;
};

}

#endif