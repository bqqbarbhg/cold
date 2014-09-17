#ifndef _COLD_SCRIPT_VALUE
#define _COLD_SCRIPT_VALUE

#include <cold/util/delegate.h>
#include <vector>

namespace cold { namespace script {

struct Object;
struct Function;
struct Instance;
struct List;
struct Value {
	enum Type {
		NONE,
		ERROR,
		INT,
		OBJECT,
		DELEGATE,
		PTR,
	};
	Value ();
	Value (Type t);
	Value (Instance* i);
	Value (const Object& o);
	Value (const List& o);
	Value (const int& i);
	Value (const Delegate<Value, const std::vector<Value>&>& d);
	Value (Value* v);

	Value operator+(const Value &rhs) const;
	Value operator*(const Value &rhs) const;
	Value operator/(const Value &rhs) const;
	Value operator%(const Value &rhs) const;
	Value operator-(const Value &rhs) const;

	operator bool() const;

	const static Value Error;
	int get_int() const;
	Object get_object() const;
	Function get_function() const;
	unsigned int get_array_length() const;
	Value* get_array_value(unsigned int id) const;
	void set(const Value& v);
	void ptr_set(const Value& v) const;
	Value ptr_get() const;
	std::string repr() const;

	Type get_type() const { return type; }
private:
	friend class Engine;
	union {
		int v_int;
		Instance* v_inst;
		Delegate<Value, const std::vector<Value>&> v_delegate;
		Value* v_ptr;
	} data;
	Type type;
};

typedef Delegate<Value, const std::vector<Value>&> ScriptDelegate;

} }

#endif