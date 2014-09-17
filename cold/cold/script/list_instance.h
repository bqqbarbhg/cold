#ifndef _COLD_SCRIPT_LIST_INSTANCE_H
#define _COLD_SCRIPT_LIST_INSTANCE_H

#include <cold/script/instance.h>
#include <cold/script/value.h>
#include <vector>
#include <string>
#include <unordered_map>

namespace cold { namespace script {

class Engine;
struct ListInstance : public Instance {
	ListInstance(Engine *e, const std::vector<Value>& vals);
	Value filter(const std::vector<Value>& params);
	Value map(const std::vector<Value>& params);

	std::string repr() const;
	Type get_type() const { return LIST; }
	bool get_member(Value* v, const std::string& str);
private:
	friend struct List;
	std::vector<Value> values;
};

} }

#endif