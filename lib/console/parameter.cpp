#include <console/parameter.h>

using namespace console;

std::ostream& console::operator<<(
	std::ostream& _stream,
	const parameter& _parameter
) {

	if(_parameter.optional) {

		_stream<<"[";
	}

	_stream<<_parameter.type;

	if(_parameter.optional) {

		_stream<<"="<<_parameter.default_value<<"]";
	}

	return _stream;
}
