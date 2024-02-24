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

/**
 * class constructor, must be hooked to an execution environment at all
 * times.
 */
							console(console_environment&);
 
/**
 * creates a command for the console. Receives the command name and a
 * vector of parameters specifying their types. Parameters are not named.
 * The command name MUST NOT contain any whitespace,
 */
	console&                map_command(
		const std::string&,
		const std::vector<parameter>&
	);

/**
 * the console can be connected to an ostream so all the string ouput of its
 * command is redirected to it. There can be only one stream connected at
 * any given time.
 */
	console&                connect_output(std::ostream& _output);

/**
 * disconects the console output stream so all string output is not redirected.
 * string output is still accessible from the result of "send" calls.
 */
	console&                disconnect_output();

/**
 * sends a string to the console to be executed.
 */
	result                  send(const std::string&);
/**
 * sends a input stream to the console to be executed
 */
	result                  send(std::istream& _input);

	private:
/**
 * internally thrown when a syntax error is detected.
 */
	struct syntax_error: public std::runtime_error {
		syntax_error(const std::string& _err):std::runtime_error{_err}{}
	};
/**
 * internally thrown when an argument is not of the expected type.
 */
	struct type_mismatch: public std::runtime_error {
		type_mismatch(const std::string& _err):std::runtime_error{_err}{}
	};

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
