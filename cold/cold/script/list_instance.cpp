#include "list_instance.h"

#include <cold/script/function.h>
#include <cold/script/engine.h>
#include <cold/script/param_list_static.h>

#include <iostream>
#include <sstream>

namespace cold { namespace script {

ListInstance::ListInstance(Engine* e, const std::vector<Value>& vals)
	: Instance(e), values(vals)
{
}
bool ListInstance::get_member(Value* v, const std::string& str) {
	if (str == "filter") {
		new (v) Value(ScriptDelegate::make<ListInstance, &ListInstance::filter>(this));
		return true;
	} else if (str == "map") {
		new (v) Value(ScriptDelegate::make<ListInstance, &ListInstance::map>(this));
		return true;
	}
	return false;
}
Value ListInstance::filter(const std::vector<Value>& params) {
	std::vector<Value> res;
	for (std::vector<Value>::iterator it = values.begin(); it != values.end(); ++it) {
		if (params[0].get_function()(*it)) {
			res.push_back(*it);
		}
	}
	return engine->add_instance(new ListInstance(engine, res));
}
Value ListInstance::map(const std::vector<Value>& params) {
	std::vector<Value> res;
	
	for (std::vector<Value>::iterator it = values.begin(); it != values.end(); ++it) {
		res.push_back(params[0].get_function()(*it));
	}
	return engine->add_instance(new ListInstance(engine, res));
}
std::string ListInstance::repr() const {
	std::stringstream s(std::ios::out);
	bool first = true;
	s << "[";
	for (std::vector<Value>::const_iterator it = values.cbegin(); it != values.cend(); ++it) {
		if (first) {
			first = false;
		} else
			s << ", ";
		s << it->repr();
	}
	s << "]";
	return s.str();
}

} }