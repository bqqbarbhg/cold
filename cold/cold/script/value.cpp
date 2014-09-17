#include "value.h"
#include <cold/util/assert.h>
#include <cold/script/instance.h>
#include <cold/script/function.h>
#include <cold/script/object.h>
#include <cold/script/list.h>

#include <iostream>
#include <ostream>
#include <sstream>

namespace cold { namespace script {

const Value Value::Error = Value(Value::ERROR);

Value::Value() {
	type = NONE;
}

Value::Value(Type t)
	: type(t)
{
}
Value::Value(Instance* i)
	: type(OBJECT)
{
	data.v_inst = i;
}
Value::Value(const Object& o)
	: type(OBJECT)
{
	data.v_inst = (Instance*)o.ptr;
}
Value::Value(const List& o)
	: type(OBJECT)
{
	data.v_inst = (Instance*)o.ptr;
}
Value::Value(const int& i)
	: type(INT)
{
	data.v_int = i;
}
Value::Value(const Delegate<Value, const std::vector<Value>&>& d)
	: type(DELEGATE)
{
	data.v_delegate = d;
}
Value::Value(Value* v)
	: type(PTR)
{
	data.v_ptr = v;
}

Value Value::operator+(const Value &rhs) const {
	if (type == rhs.type && type == INT) {
		return data.v_int + rhs.data.v_int;
	}
	return Value::Error;
}
Value Value::operator-(const Value &rhs) const {
	if (type == rhs.type && type == INT) {
		return data.v_int - rhs.data.v_int;
	}
	return Value::Error;
}
Value Value::operator*(const Value &rhs) const {
	if (type == rhs.type && type == INT) {
		return data.v_int * rhs.data.v_int;
	}
	return Value::Error;
}
Value Value::operator/(const Value &rhs) const {
	if (type == rhs.type && type == INT) {
		return data.v_int / rhs.data.v_int;
	}
	return Value::Error;
}
Value Value::operator%(const Value &rhs) const {
	if (type == rhs.type && type == INT) {
		return data.v_int % rhs.data.v_int;
	}
	return Value::Error;
}

Value::operator bool() const {
	switch (type) {
	case INT:
		return data.v_int != 0;
	}
	return false;
}

int Value::get_int() const {
	return data.v_int;
}
Object Value::get_object() const {
	return Object(reinterpret_cast<ObjectInstance*>(data.v_inst));
}
Function Value::get_function() const {
	return Function((FunctionInstance*)data.v_inst);
}

std::string Value::repr() const {
	std::stringstream s(std::ios::out);
	switch (type) {
	case INT:
		s << data.v_int;
		break;
	case OBJECT:
		s << data.v_inst->repr();
		break;
	case DELEGATE:
		s << data.v_delegate;
		break;
	case NONE:
		s << "none";
		break;
	}
	return s.str();
}

void Value::set(const Value& v) {
	if (v.type == INT) {
		type = INT;
		data.v_int = v.data.v_int;
	} else if (v.type == OBJECT) {
		type = OBJECT;
		data.v_inst = v.data.v_inst;
	} else if (v.type == DELEGATE) {
		type = DELEGATE;
		data.v_delegate = v.data.v_delegate;
	}
}
void Value::ptr_set(const Value& v) const {
	if (type == PTR) {
		data.v_ptr->set(v);
	}
}

Value Value::ptr_get() const {
	if (type != PTR)
		return Value::Error;
	return *data.v_ptr;
}


} }