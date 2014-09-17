#ifndef _COLD_SCRIPT_PARAM_H
#define _COLD_SCRIPT_PARAM_H

#include <string>

namespace cold { namespace script {

struct Param {
	enum Flag {
		NONE = 0,
		COPY = 1 << 0,
	};
	Param();
	bool operator==(const Param& rhs) const;
	bool operator!=(const Param& rhs) const;
	std::string name;
	Flag flags;
	std::string repr() const;
};

} }

#endif