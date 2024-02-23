#pragma once

#include "definitions.h"
#include <string>
#include <ostream>

namespace console {

struct argument {

						argument(int );
						argument(const std::string&);
						argument(double);
						argument(bool);

	const types type;

	int                 get_int() const {check_type(types::integer); return intval;}
	const std::string&  get_string() const {check_type(types::string); return stringval;}
	double              get_decimal() const {check_type(types::decimal); return decimalval;}
	bool                get_boolean() const {check_type(types::boolean); return booleanval;}

	private:

	void                check_type(types) const;

	int                 intval{0};
	std::string         stringval;
	double              decimalval{0.0};
	bool                booleanval{false};
};

std::ostream& operator<<(std::ostream&, const argument&);

}
