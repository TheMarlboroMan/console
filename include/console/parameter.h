#pragma once

#include "argument.h"
#include "definitions.h"

namespace console {

/**
 * represents a command parameter, which must have a type. These are used 
 * when mapping a command for the console by specifying the command name and
 * the number and type of parameters it expects.
 * The optional and default values are unimplemented as of now.
 */
struct parameter {

	types           type;
/**
 * unimplemented
 */
	bool            optional{false};
/**
 * unimplemented
 */
	argument        default_value{false};
};
}
