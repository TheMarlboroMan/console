#include <console/definitions.h>

using namespace console;

std::ostream& console::operator<<(
	std::ostream& _stream,
	const types& _type
) {

	switch(_type) {
		case types::string: _stream<<"string"; break;
		case types::integer: _stream<<"integer"; break;
		case types::decimal: _stream<<"decimal"; break;
		case types::boolean: _stream<<"boolean"; break;
	}

	return _stream;
}
