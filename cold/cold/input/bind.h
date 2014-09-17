#ifndef _COLD_INPUT_BIND_H
#define _COLD_INPUT_BIND_H

#include <glm/glm.hpp>
#include <cold/input/input.h>
#include <vector>

namespace cold {

template <typename T>
inline T _t_default();
template <typename T>
inline void _t_reduce(T&, const T&);

template <> inline bool _t_default<bool>() {
	return false;
}
template <> inline void _t_reduce<bool>(bool& a, const bool& b) {
	a = a || b;
}

template <> inline glm::vec2 _t_default<glm::vec2>() {
	return glm::vec2();
}
template <> inline void _t_reduce<glm::vec2>(glm::vec2& a, const glm::vec2& b) {
	a += b;
}

template <typename T>
class Bind {
public:
	~Bind() {
		for (std::vector<Input<T>*>::const_iterator it = _inputs.cbegin(); it != _inputs.cend(); ++it)
			delete *it;
	}
	T get() const {
		T value = _t_default<T>();
		for (std::vector<Input<T>*>::const_iterator it = _inputs.cbegin(); it != _inputs.cend(); ++it)
			_t_reduce<T>(value, (*it)->get());
		return value;
	}
	void add(Input<T>* input) {
		_inputs.push_back(input);
	}
	void operator+= (Input<T>* input) {
		add(input);
	}
private:
	std::vector<Input<T>*> _inputs;
};

}

#endif