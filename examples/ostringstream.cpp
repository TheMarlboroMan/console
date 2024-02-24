#include <console/console.h>
#include <iostream>
#include <sstream>

class env:
	public console::console_environment {

	public:

	bool exit=false;
	std::ostringstream          outstream;

	private:

	virtual console::result      execute_cmd(
		const std::string& _cmdname,
		const std::vector<console::argument>& _args

	) {

		if(_cmdname=="exit") {

			exit=true;
			return console::result{console::result::ok, "will exit"};
		}

		if(_cmdname=="help") {

			return console::result{console::result::ok, "valid commands are help, hello(str), exit and sum(int, int)"};
		}

		if(_cmdname=="hello") {

			std::stringstream ss;
			ss<<"hello to you "<<_args[0].get_string();

			return console::result{console::result::ok, ss.str()};
		}

		if(_cmdname=="sum") {

			int a=_args[0].get_int();
			int b=_args[1].get_int();
			std::stringstream ss;
			ss<<"the sum of "<<a<<" and "<<b<<" is "<<(a+b);
			return console::result{console::result::ok, ss.str()};
		}

		return console::result{console::result::ok, "default response one should never have to read."};
	}

};

int main(int, char **) {

	env e;
	console::console c{e};

	c.connect_output(e.outstream);

	auto position=e.outstream.tellp();

	c.map_command("hello", { {console::types::string} });
	c.map_command("exit", {});
	c.map_command("help", {});
	c.map_command("sum", { {console::types::integer}, {console::types::integer}});

	while(!e.exit) {

		std::cout<<">>";
		std::string in;
		std::getline(std::cin, in);
		c.send(in);

		if(e.outstream.tellp() != position) {

			std::cout<<e.outstream.str()<<std::endl;
			e.outstream.str("");  //clear the buffer...
			position=e.outstream.tellp();
		}
	}

	return 0;
}
