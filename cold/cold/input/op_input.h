#ifndef _COLD_INPUT_AND_INPUT_H
#define _COLD_INPUT_AND_INPUT_H

#include <cold/input/input.h>
#include <cold/util/unique_ptr.h>

namespace cold {

// Passes two inputs through a function
// T: Type of the input
// F: Type of the function
template <typename T, T (*Fn)(T, T)>
class FnPtrInput : public Input<T> {
public:
	// a: First input
	// b: Second input
	FnPtrInput(Input<T>* a, Input<T>* b)
		: a(a), b(b)
	{
	}

	virtual T get() const {
		return Fn(a->get(), b->get());
	}

private:
	UniquePtr<Input<T>> a, b;
};

namespace impl { namespace input {
	bool and(bool a, bool b) { return a && b; }
	bool or(bool a, bool b) { return a || b; }
} }

typedef FnPtrInput<bool, &and> AndInput;
typedef FnPtrInput<bool, &or> OrInput;

}

#endif