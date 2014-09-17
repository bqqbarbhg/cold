#ifndef _COLD_SCRIPT_PARAM_LIST_STATIC_H
#define _COLD_SCRIPT_PARAM_LIST_STATIC_H

#include <cold/script/param_list.h>
#include <cold/script/value.h>

namespace cold { namespace script {

template <int N>
struct ParamListStatic : public ParamList {
	ParamListStatic()
		: ParamList(values, values + N)
	{
	}
	Value& operator[](unsigned int i) {
		return values[i];
	}
private:
	Value values[N];
};

} }

#endif