#pragma once

#include "argument.h"
#include "definitions.h"

namespace console {

struct parameter {

	types           type;
	bool            optional{false};
	argument        default_value{false};
};
}
