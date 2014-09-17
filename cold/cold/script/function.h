#ifndef _COLD_SCRIPT_FUNCTION_H
#define _COLD_SCRIPT_FUNCTION_H

#include <cold/script/instance_handle.h>
#include <cold/script/value.h>
#include <vector>

namespace cold { namespace script {

struct ParamList;
struct FunctionInstance;
struct Function : public InstanceHandle<FunctionInstance> {
	explicit Function(FunctionInstance* f) : InstanceHandle<FunctionInstance>(f) { }
	Value operator()(const Value& v);
	Value operator()(const ParamList& p);
};

} }

#endif