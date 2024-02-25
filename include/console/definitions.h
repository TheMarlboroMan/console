#pragma once

#include <ostream>

namespace console {

/**
 * argument and parameter types.
 */
enum class types{string, integer, decimal, boolean};

std::ostream& operator<<(std::ostream&, const types&);

}
