#include <console/command_definition.h>

using namespace console;

std::ostream& console::operator<<(
	std::ostream& _stream,
	const command_definition& _command
) {

	_stream<<_command.name<<"(";
	for(const auto& param : _command.parameters) {

		_stream<<param<<", ";
	}

	_stream<<")";

	return _stream;
}
