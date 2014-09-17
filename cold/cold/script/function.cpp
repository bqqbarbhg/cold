#include "function.h"
#include <cold/script/function_instance.h>
#include <cold/script/param_list_static.h>

namespace cold { namespace script {


Value Function::operator()(const Value& v) {
	ParamListStatic<1> p;
	p[0] = v;
	return ptr->call(p);
}
Value Function::operator()(const ParamList& params) {
	return ptr->call(params);
}

} }