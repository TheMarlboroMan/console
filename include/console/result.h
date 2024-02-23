#pragma once

#include <string>

namespace console {

struct result {

	enum status {
		ok=0,
		err=1,
		bad_command=10,
		syntax_error=11,
		missing_args=12,
		type_mismatch=13
	};

	const int code{0};
	const std::string output;
};

}
