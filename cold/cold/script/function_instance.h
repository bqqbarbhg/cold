#ifndef _COLD_SCRIPT_FUNCTION_INSTANCE_H
#define _COLD_SCRIPT_FUNCTION_INSTANCE_H

#include <vector>
#include <cold/script/instance.h>
#include <cold/script/value.h>
#include <cold/script/engine.h>

namespace cold { namespace script {

struct FunctionDefinition;
class Engine;
struct ParamList;
struct FunctionInstance : Instance {
	FunctionInstance(Engine* engine, FunctionDefinition *def);

	Type get_type() const { return FUNCTION; }
	std::string repr() const;

	Value call(const ParamList& params) { return engine->call(this, params); }

	FunctionDefinition *definition;
};

} }

#endif