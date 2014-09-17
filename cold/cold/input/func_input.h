#ifndef _COLD_INPUT_AND_INPUT_H
#define _COLD_INPUT_AND_INPUT_H

#include <cold/input/input.h>
#include <cold/util/unique_ptr.h>

namespace cold {

// Passes two inputs through a function
// T: Type of the input
// F: Functor of type T(T, T)
template <typename T, typename F>
class FuncInput : public Input<T> {
public:
	// o: Operation to pass `a` and `b` through
	//    Prototype T(T, T)
	// a: First input
	// b: Second input
	FuncInput(F o, Input<T>* a, Input<T>* b)
		: op(o), a(a), b(b)
	{
	}

	virtual T get() const {
		return op(a->get(), b->get());
	}

private:
	F op;
	UniquePtr<Input<T>> a, b;
};

// Creates an new OpInput<T, F> use so you don't have to write
// functor type, especially when it's unutterable
// Allocates a new Input with `new` so you have to free it with delete
// or wrap it into a UniquePtr
// <T>: Output type of the input
// <F>: Functor type
// f: Function to use in the operation
// a: First source input
// b: Second source input
template <typename T, typename F>
FuncInput<T, F>* make_func_input(F f, Input<T>* a, Input<T>* b);

}

#endif