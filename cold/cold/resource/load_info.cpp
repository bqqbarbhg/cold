#include "load_info.h"

namespace cold {

void ResourceLoadInfo::set_arg(const std::string& k, const std::string& v) {
	args[k] = v;
}
void ResourceLoadInfo::set_flag(const std::string& k) {
	flags.insert(k);
}
bool ResourceLoadInfo::get_flag(const std::string& s) const {
	return flags.find(s) != flags.end();
}
bool ResourceLoadInfo::get_arg(const std::string& k, std::string& s) const {
	auto it = args.find(k);
	if (it == args.end()) return false;
	s = it->second;
	return true;
}

}