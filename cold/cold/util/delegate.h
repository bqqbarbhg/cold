#ifndef _COLD_UTIL_DELEGATE_H
#define _COLD_UTIL_DELEGATE_H

#include <iostream>
#include <vector>

namespace cold {

template <class Ret, class Par>
class Delegate {
public:

	template <class Class, Ret (Class::*Method)(Par)>
	static Delegate make(Class* object) {
		Delegate d;
		d.object_ptr = object;
		d.stub_ptr = &method_stub<Class, Method>;
		return d;
	}

	Ret operator()(Par p) {
		return (*stub_ptr)(object_ptr, p);
	}

private:
	typedef Ret (*stub_type)(void*, Par);
	
	friend std::ostream & operator <<(std::ostream& lhs, const Delegate<Ret, Par>& rhs) {
		lhs << "<" << rhs.object_ptr << ">::<" << rhs.stub_ptr << ">";
		return lhs;
	}

	void* object_ptr;
	stub_type stub_ptr;

	template <class Class, Ret (Class::*Method)(Par)>
	static Ret method_stub(void* obj, Par p) {
		return (static_cast<Class*>(obj)->*Method)(p);
	}
};

}

#endif