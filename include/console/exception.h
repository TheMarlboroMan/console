#pragma once

#include <stdexcept>
#include <string>

namespace console {

/**
 * thrown at runtime, must be caught by the implementor.
 */
struct runtime_error: public std::runtime_error {
	runtime_error(const std::string& _err):std::runtime_error{_err}{}
};
}
