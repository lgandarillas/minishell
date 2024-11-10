# Minishell

A shell inspired by bash, developed as part of the 42 curriculum. This shell interprets and executes commands, handles pipes and redirections, and includes a set of built-in commands.

## Overview

Minishell is designed to:
- Parse and execute commands with arguments.
- Handle absolute, relative, and environment paths.
- Provide support for pipes (`|`) and redirections (`<`, `>`, `>>`, `<<`).
- Include environment variable handling (`$VAR` and `$?`).
- Support interactive shell control with `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`.

## Features

### Built-in Commands
Minishell implements the following built-in functions directly without external executables:
- `echo` with `-n` option
- `cd` with relative or absolute paths
- `pwd` (no options)
- `export` (no options)
- `unset` (no options)
- `env` (no options)
- `exit` with optional exit status

### Additional Features
- **Quoting**: Supports single (`'`) and double (`"`) quotes for string handling.
- **History**: Tracks command history during the session.
- **Signals**: Handles `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` like bash.
- **Environment Variables**: Expands `$VAR` and includes support for `$?` (last exit status).

## Setup and Usage

1. Clone the repository:
	```bash
	git clone https://github.com/lgandarillas/minishell.git
	```
	```bash
	cd minishell
	```

2. Compile the project:
	```bash
	make
	```

3. Run the shell:
	```bash
	./minishell
	```

## Contribution
This project was developed collaboratively by [@alejandquintero](https://github.com/alejandquintero) and [@lgandarillas](https://github.com/lgandarillas).