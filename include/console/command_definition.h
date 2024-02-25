#pragma once

#include "parameter.h"
#include <vector>
#include <string>
#include <ostream>

namespace console {

/**
 * definition of an command in the console, a name and parameters
 */
struct                  command_definition {
	const std::string               name;
	const std::vector<parameter>    parameters;
};

std::ostream& operator<<(std::ostream&, const command_definition&);
}
