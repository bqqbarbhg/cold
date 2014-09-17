#include "io.h"

#include <iostream>
#include <fstream>

namespace cold {

std::string read_file_string(const char* file) {
	std::ifstream s(file, std::ios::in | std::ios::binary);
	if (s) {
		std::string ret;
		s.seekg(0, std::ios::end);
		ret.resize((unsigned int)s.tellg());
		s.seekg(0, std::ios::beg);
		s.read(&ret[0], ret.size());
		s.close();
		return ret;
	}
	throw errno;
}

}