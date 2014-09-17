#include "param.h"

#include <iostream>
#include <ostream>
#include <sstream>

namespace cold { namespace script {

Param::Param()
	: flags(NONE)
{
}

bool Param::operator==(const Param& rhs) const {
	if (flags != rhs.flags) return false;
	return name == rhs.name;
}
bool Param::operator!=(const Param& rhs) const {
	return !(*this == rhs);
}

std::string Param::repr() const {
	std::stringstream s(std::ios::out);
	if (flags & COPY)
		s << "copy ";
	s << name;
	return s.str();
}

} }