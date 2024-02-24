#pragma once

#include <string>

namespace console {

/**
 * represents the result of executing a console command. The result has two
 * parts: an integer to represent a status code and a string to represent
 * a readable output. A few status codes are standarized for ok, error,
 * unknown commmand, missing arguments, syntax errors and type mismatches.
 */
struct result {

	enum status {
		ok=0,
		err=1,
		bad_command=10,
		syntax_error=11,
		missing_args=12,
		type_mismatch=13
	};

/**
 * readonly result code.
 */
	const int code{0};
/**
 * readonly string output.
 */
	const std::string output;
};

}
