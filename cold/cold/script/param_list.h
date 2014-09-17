#ifndef _COLD_SCRIPT_PARAM_LIST_H
#define _COLD_SCRIPT_PARAM_LIST_H

namespace cold { namespace script {

struct Value;
struct ParamList {
	ParamList(Value *b, Value *e)
		: begin(b), end(e)
	{
	}
	Value *begin, *end;
};

} }

#endif