#ifndef _COLD_SCRIPT_OBJECT_H
#define _COLD_SCRIPT_OBJECT_H

#include <cold/script/instance_handle.h>

namespace cold { namespace script {

struct ObjectInstance;
struct Object : public InstanceHandle<ObjectInstance> {
	explicit Object(ObjectInstance* i) : InstanceHandle<ObjectInstance>(i) { }
};

} }

#endif