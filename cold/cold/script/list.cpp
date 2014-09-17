#include "list.h"
#include <cold/script/list_instance.h>

namespace cold { namespace script {

List::List(ListInstance *i)
	: InstanceHandle<ListInstance>(i)
{
}

void List::push(const Value& v) {
	ptr->values.push_back(v);
}

} }