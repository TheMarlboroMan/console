#pragma once

#include "result.h"
#include "argument.h"
#include <string>
#include <vector>

namespace console {

/**
 *The whole public and virtual private thing is the non-virtual interface
*pattern. I just wanted to try it out.
*/
class console_environment {

	public:

	console::result             execute(
		const std::string&,
		const std::vector<console::argument>&
	);

	private:

	virtual console::result     execute_cmd(
		const std::string&, 
		const std::vector<console::argument>&
	)=0;
};
}

