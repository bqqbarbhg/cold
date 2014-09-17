#ifndef _COLD_SCRIPT_INSTANCE_H
#define _COLD_SCRIPT_INSTANCE_H

#include <string>

namespace cold { namespace script {

struct Value;
class Engine;
struct Instance {
	enum Type {
		OBJECT,
		FUNCTION,
		LIST,
	};
	Instance(Engine *engine);

	template <class T>
	T* cast() { return static_cast<T*>(this); }
	template <class T>
	const T* cast_const() const { return static_cast<T*>(this); }

	virtual std::string repr() const = 0;
	virtual Type get_type() const = 0;
	virtual bool get_member(Value* v, const std::string& str) { return false; }
	virtual Value* get_member_ref(const std::string& str) { return 0; }
protected:
	Engine *engine;
private:
	template <class T>
	friend struct InstanceHandle;
	friend class Engine;
	unsigned int unmanaged_ptr_count;
	bool mark;
};

} }

#endif