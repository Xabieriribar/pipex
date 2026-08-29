# Pipex

Pipex recreates Unix pipeline behavior in C. It connects commands through pipes, redirects input and output, and manages the lifecycle of the processes involved.

The mandatory program behaves like:

~~~bash
< infile cmd1 | cmd2 > outfile
~~~

The bonus implementation supports an arbitrary pipeline:

~~~bash
< infile cmd1 | cmd2 | cmd3 > outfile
~~~

## Technical implementation

The project combines:

- fork for process creation
- pipe for inter-process communication
- dup2 for redirecting standard input and output
- execve for replacing child processes with commands
- PATH parsing for executable resolution
- waitpid for process synchronization and exit handling
- Defensive cleanup of file descriptors and allocated memory

## Build

~~~bash
make
make bonus
~~~

## Usage

~~~bash
./pipex infile "ls -l" "wc -l" outfile
~~~

Bonus:

~~~bash
./pipex infile "grep error" "sort" "uniq -c" outfile
~~~

## Testing

Compare Pipex with the equivalent shell command:

~~~bash
echo "Hello World" > infile
./pipex infile "cat" "wc -w" outfile_pipex
< infile cat | wc -w > outfile_shell
diff outfile_pipex outfile_shell
~~~

Check errors and memory handling with invalid files, unknown commands and Valgrind:

~~~bash
valgrind --leak-check=full --show-leak-kinds=all \
  ./pipex infile "cat" "wc -l" outfile
~~~

## What this project demonstrates

Pipex is a compact systems-programming project that shows how a shell constructs a pipeline from low-level Unix primitives. It prepared me for the more complex parser and executor architecture used later in Minishell.
