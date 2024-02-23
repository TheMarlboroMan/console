#pragma once

#include <stdexcept>
#include <string>

namespace console {

struct syntax_error: public std::runtime_error {
	syntax_error(const std::string& _err):std::runtime_error{_err}{}
};
struct type_mismatch: public std::runtime_error {
	type_mismatch(const std::string& _err):std::runtime_error{_err}{}
};
struct runtime_error: public std::runtime_error {
	runtime_error(const std::string& _err):std::runtime_error{_err}{}
};
}
