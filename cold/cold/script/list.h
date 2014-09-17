#ifndef _COLD_SCRIPT_LIST_H
#define _COLD_SCRIPT_LIST_H

#include <cold/script/instance_handle.h>

namespace cold { namespace script {

struct ListInstance;
struct List : InstanceHandle<ListInstance> {
	explicit List(ListInstance* i);

	void push(const Value& v);
};

} }

#endif