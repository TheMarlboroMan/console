#include <console/console.h>
#include <console/exception.h>
#include <ctype.h>
#include <sstream>
#include <iostream>

using namespace console;

console::console::console(console_environment& _env)
	:environment{_env}
{}

console::console& console::console::map_command(
	const std::string& _command_name,
	const std::vector<parameter>& _parameters
) {

	if(std::string::npos != _command_name.find_first_of("\t\n ")) {

		std::stringstream ss;
		ss<<"invalid command name '"<<_command_name<<"'. command names must not contain whitespace";
		throw runtime_error(ss.str());
	}

	commands.insert(std::make_pair(_command_name, command_definition{_command_name, _parameters}));
	return *this;
}

console::console& console::console::connect_output(
	std::ostream& _output
) {

	output=&_output;
	return *this;
}

console::console& console::console::disconnect_output() {

	output=nullptr;
	return *this;
}

result console::console::send(
	std::istream& _input
) {

	auto result=execute_command(_input);

	if(nullptr!=output) {

		(*output)<<result.output<<std::endl;
	}

	return result;
}

result console::console::send(
	const std::string& _input
) {

	std::istringstream iss(_input);
	return send(iss);
}

void console::console::push_arg_and_clear_buffer(
	std::vector<argument>& _args, 
	std::string& _buffer,
	const std::vector<parameter>& _parameters
) const {

	if(!_buffer.size()) {

		return;
	}

	//Any extra arguments will be ignored.
	if(_parameters.size() <= _args.size()) {

		return;
	}

	auto fail=[&](const std::string _err) {

		std::stringstream ss;
		ss<<_err<<", got '"<<_buffer<<"'";
		throw type_mismatch(ss.str());
	};

	switch(_parameters.at(_args.size()).type) {

		case types::integer:

			if(!is_integer(_buffer)) {

				fail("expected integer");
			}

			_args.push_back({std::stoi(_buffer)});
		break;
		case types::decimal:

			if(!is_decimal(_buffer)) {

				fail("expected decimal");
			}

			_args.push_back({std::stod(_buffer)});
		break;
		case types::boolean:

			if(_buffer=="true") {

				_args.push_back({true});

			}
			else if(_buffer=="false") {

				_args.push_back({false});
			}
			else {

				std::stringstream ss;
				ss<<"expected boolean true|false"<<_buffer;
			}
		break;
		case types::string:

			_args.push_back({_buffer});
		break;
	}

	_buffer.clear();
}

result console::console::execute_command(
	std::istream& _input
) {

	//Check there is something in the input...
	int c=_input.peek(); 
	if(c == EOF) {

		return {0, ""};
	}

	//Extract the command...
	std::string cmdname;
	_input>>cmdname;

	if(!commands.count(cmdname)) {

		std::stringstream ss;
		ss<<"command "<<cmdname<<" not found";
		return {result::bad_command, ss.str()};
	}

	const auto& cmd_definition=commands.at(cmdname);

	try {

		std::vector<argument> arguments=collect_arguments(_input, cmd_definition);

		//Are we missing any args?
		if(arguments.size() < cmd_definition.parameters.size()) {

			std::stringstream ss;
			ss<<"missing arguments, expected "<<cmd_definition.parameters.size()<<", got "<<arguments.size();
			return {result::missing_args, ss.str()};
		}

		return environment.execute(cmdname, arguments);
	}
	catch(type_mismatch& e) {

		return {result::type_mismatch, e.what()};
	}
	catch(syntax_error& e) {

		return {result::syntax_error, e.what()};
	}
}

std::vector<argument> console::console::collect_arguments(
	std::istream& _input,
	const command_definition& _cmd_definition
) const {

	std::vector<argument> arguments;

	if(_input.eof()) {

		return arguments;
	}

	std::string buffer;
	bool is_string=false;

	while(true) {

		char cur=0;
		_input.get(cur);

		if(_input.eof()) {

			goto are_we_done;
		}

		if(cur=='"') {

			is_string=!is_string;

			//We just finished a string, which is an arg on itself.
			if(!is_string) {

				goto push_arg;
			}

			goto are_we_done;
		}

		//A space may be...
		if(cur==' ') {

			//... part of a string ...
			if(is_string) {

				buffer+=cur;
				goto are_we_done;
			}

			//this will discard sequences of non-string spaces.
			goto push_arg;
		}

		buffer+=cur;
		goto are_we_done;

		push_arg:

		push_arg_and_clear_buffer(arguments, buffer, _cmd_definition.parameters);

		are_we_done:

		if(_input.eof()) {

			if(is_string) {

				throw syntax_error("syntax error: illegal unclosed string");
			}

			push_arg_and_clear_buffer(arguments, buffer, _cmd_definition.parameters);
			break;
		}
	}

	return arguments;
}

bool console::console::is_integer(
	const std::string& _value
) const {

	for(const auto c : _value) {

		if(!std::isdigit(static_cast<unsigned char>(c))) { //this is common in the ctype header.

			return false;
		}
	}

	return true;
}

bool console::console::is_decimal(
	const std::string& _value
) const {

	for(const auto c : _value) {

		if(c=='.') {

			continue;
		}

		if(!std::isdigit(static_cast<unsigned char>(c))) { 

			return false;
		}
	}

	return true;
}
