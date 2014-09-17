#ifndef _COLD_SCRIPT_OBJECT_INSTANCE_H
#define _COLD_SCRIPT_OBJECT_INSTANCE_H

#include <cold/script/instance.h>
#include <map>
#include <string>
#include <cold/script/value.h>

namespace cold { namespace script {

class Engine;
struct ObjectInstance : public Instance {
	ObjectInstance(Engine *e);
	Type get_type() const { return OBJECT; }
	std::map<std::string, Value> values;
	std::string repr() const;
	bool get_member(Value* v, const std::string& str);
	Value* get_member_ref(const std::string& str);
};

} }

#endif