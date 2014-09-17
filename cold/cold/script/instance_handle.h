#ifndef _COLD_SCRIPT_INSTANCE_HANDLE_H
#define _COLD_SCRIPT_INSTANCE_HANDLE_H

#include <cold/script/instance.h>

namespace cold { namespace script {

struct Value;
struct Instance;
template <class T>
struct InstanceHandle {
public:
	InstanceHandle (T *o) : ptr(o)
	{
		((Instance*)ptr)->unmanaged_ptr_count++;
	}
	InstanceHandle (const InstanceHandle<T>& o) : ptr(o.ptr)
	{
		((Instance*)ptr)->unmanaged_ptr_count++;
	}
	~InstanceHandle() {
		((Instance*)ptr)->unmanaged_ptr_count--;
	}
	InstanceHandle& operator=(const InstanceHandle<T>& o) {
		if (o.ptr == ptr)
			return *this;
		((Instance*)o.ptr)->unmanaged_ptr_count++;
		((Instance*)ptr)->unmanaged_ptr_count--;
		ptr = o.ptr;
		return *this;
	}
protected:
	friend struct Value;
	T* ptr;
};

} }

#endif