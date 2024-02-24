#pragma once

#include "definitions.h"
#include <string>
#include <ostream>

namespace console {

/**
 * represents an argument (the concrete realization of a parameter). These will
 * be used in the console environment to pass information forth to the 
 * console. Supported types are integers, strings, decimals (double) and
 * booleans. 
 * An argument can only be of a type and cannot be casted. Values are to be
 * retrieved via the get_int/string/decimal/boolean methods according to 
 * the constant property "type". Attempting to call an invalid getter will
 * cause an exception to be thrown.
 */
struct argument {

/**
 * constructor for an integer argument
 */
						argument(int );
/**
 * constructor for a string argument.
 */
						argument(const std::string&);
/**
 * constructor for a decimal argument.
 */
						argument(double);
/**
 * constructor for a boolean argument.
 */
						argument(bool);

/**
 * readonly type.
 */
	const types type;


/**
 * retrieves the integer value. Will throw if the argument is not of the 
 * integer type.
 */
	int                 get_int() const {check_type(types::integer); return intval;}
/**
 * retrieves the string value. Will throw if the argument is not of the string
 * type.
 */
	const std::string&  get_string() const {check_type(types::string); return stringval;}
/**
 * retrieves the decimal value. Will throw if the argument is not of the decimal
 * type.
 */
	double              get_decimal() const {check_type(types::decimal); return decimalval;}
/**
 * retrieves the boolean value. Will throw if the argument is not of the boolean
 * type.
 */
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
