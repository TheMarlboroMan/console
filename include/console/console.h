#pragma once

#include "console_environment.h"
#include "result.h"
#include "parameter.h"
#include "argument.h"
#include <string>
#include <vector>
#include <ostream>
#include <map>

namespace console {

class console {

	public:

							console(console_environment&);

	console&                map_command(
		const std::string&,
		const std::vector<parameter>&
	);

	console&                connect_output(std::ostream& _output);

	console&                disconnect_output();

	result                  send(std::istream& _input);

	private:

	struct                  command_definition {
		const std::string               name;
		const std::vector<parameter>    parameters;
	};

	void                    push_arg_and_clear_buffer(
		std::vector<argument>&, 
		std::string&,
		const std::vector<parameter>&
	) const; 

	result                   execute_command(std::istream&);

	std::vector<argument>    collect_arguments(
		std::istream&,
		const command_definition&
	) const; 

	bool                    is_integer(const std::string&) const;
	bool                    is_decimal(const std::string&) const;

	console_environment&                        environment;
	std::map<std::string, command_definition>   commands;
	std::ostream*                               output{nullptr};
};
}
