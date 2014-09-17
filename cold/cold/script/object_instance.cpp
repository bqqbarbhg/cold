#include "object_instance.h"

#include <iostream>
#include <sstream>

namespace cold { namespace script {

ObjectInstance::ObjectInstance(Engine *e)
	: Instance(e)
{
}

bool ObjectInstance::get_member(Value* v, const std::string& str) {
	new (v) Value(values[str]);
	return true;
}
Value* ObjectInstance::get_member_ref(const std::string& str) {
	return &values[str];
}

std::string ObjectInstance::repr() const {
	std::stringstream s(std::ios::out);
	s << "{";
	bool first = true;
	for (std::map<std::string, Value>::const_iterator it = values.cbegin(); it != values.cend(); ++it) {
		if (first) {
			first = false;
			s << " ";
		} else
			s << ", ";
		s << it->first << ": " << it->second.repr();

	}
	s << " }";
	return s.str();
}

} }