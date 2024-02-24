#pragma once

#include "result.h"
#include "argument.h"
#include <string>
#include <vector>

namespace console {

/**
 * the console must be hooked to an execution environment that is able
 * to carry out actions in response to commands. This is the interface for
 * these enviroments.
 *  The whole public and virtual private thing is the non-virtual interface
 * pattern. I just wanted to try it out.
*/
class console_environment {

	public:

/**
 * public execution interface, receives the name of the command and a vector
 * of arguments. Arguments will be evaluated and checked against the command
 * by the console. Missing arguments will be treated as an error. Excess
 * arguments will be ignored.
 */
	console::result             execute(
		const std::string&,
		const std::vector<console::argument>&
	);

	private:

/**
 * must carry on the execution of the command and return the appropriate 
 * result.
 */
	virtual console::result     execute_cmd(
		const std::string&, 
		const std::vector<console::argument>&
	)=0;
};
}

