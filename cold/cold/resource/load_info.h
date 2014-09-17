#ifndef _COLD_RESOURCE_LOAD_INFO_H
#define _COLD_RESOURCE_LOAD_INFO_H

#include <string>
#include <set>
#include <map>

namespace cold {

struct ResourceLoadInfo {
	// Sets an argument `k = v`
	// k: Name of the argument
	// v: Value of the argument
	void set_arg(const std::string& k, const std::string& v);
	// Sets a flag
	// k: Flag name to set
	void set_flag(const std::string& k);
	// Returns whteher a flag is set
	// k: Name of the flag
	bool get_flag(const std::string& k) const;
	// Gets an argument from the load info
	// k: Name of the argument
	// s: Reference to string to store the value into
	// returns: Whether the argument existed with name `k`
	bool get_arg(const std::string& k, std::string& s) const;
private:
	std::map<std::string, std::string> args;
	std::set<std::string> flags;
};

}

#endif