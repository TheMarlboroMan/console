# console

A simple console put together in an afternoon. The intention here is to be
able to connect a text stream source to existing projects to help in the
debugging process (think a game and being able to say move_player_to x y or
print_collisions).

Many features and proper documentation are missing.

## overview

- We need a class that implements a console_environment. This is where console
commands will get executed.
- The console is built passing this environment.
- Commands are added to the console (a command is a string and a number+type
    or parameters.
- The console can be hooked to a std::ostream so we can get its output.
- The method send (I think) can be invoked on the console with an input
    stream. This stream should contain a command name and its arguments.
- The command and the arguments are passed along to the console_environment,
    which must do the work.

## parameter types

Command parameters are separated by whitespace.
The following types are supported for command parameters.

- integer
- double
- boolean (true or false)
- strings (bash style, use quotes to be able to add space).
