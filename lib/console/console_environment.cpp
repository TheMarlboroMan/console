#include <console/console_environment.h>

using namespace console;

console::result console_environment::execute(
		const std::string& _cmd_name,
		const std::vector<console::argument>& _args
) {

	return execute_cmd(_cmd_name, _args);
}
