#include <console/argument.h>
#include <console/exception.h>

using namespace console;

argument::argument(int _val)
	:type{types::integer}, intval{_val}
{}

argument::argument(const std::string& _val)
	:type{types::string}, intval{0}, stringval{_val}
{}

argument::argument(double _val)
	:type{types::decimal}, intval{0}, stringval{}, decimalval{_val}
{}

argument::argument(bool _val)
	:type{types::decimal}, intval{0}, stringval{}, decimalval{0.0}, booleanval{_val}
{}

void argument::check_type(types _type) const {

	if(type!=_type) {

		throw runtime_error("argument type and value mismatch");
	}
}

std::ostream& console::operator<<(std::ostream& _stream, const argument& _arg) {

	switch(_arg.type) {

		case types::integer: _stream<<_arg.get_int(); break;
		case types::decimal: _stream<<_arg.get_decimal(); break;
		case types::string: _stream<<_arg.get_string(); break;
		case types::boolean: _stream<<_arg.get_boolean(); break;
	}

	return _stream;
}
