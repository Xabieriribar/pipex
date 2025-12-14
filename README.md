# Pipex

## Description
This project aims to deepen your understanding of two concepts that you already know: Redirections and Pipes. It is an implementation of the pipe mechanism in UNIX.

The program `pipex` behaves exactly like the shell command:
```bash
< file1 cmd1 | cmd2 > file2
```

## Compilation

To compile the mandatory part:
```bash
make
```

To compile with bonuses (multiple pipes):
```bash
make bonus
```

## Usage

### Mandatory
```bash
./pipex file1 cmd1 cmd2 file2
```
- `file1`: Input file.
- `cmd1`: First command.
- `cmd2`: Second command.
- `file2`: Output file.

### Bonus (Multiple Pipes)
```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdN file2
```
Behaves like:
```bash
< file1 cmd1 | cmd2 | cmd3 ... | cmdN > file2
```

## Testing Guide

### Manual Testing
To verify your project works correctly, you should compare its behavior against the actual shell commands.

#### 1. Setup
Create a dummy input file:
```bash
echo "Hello World" > infile
```

#### 2. Execution
Run your program:
```bash
./pipex infile "ls -l" "wc -l" outfile_pipex
```

Run the shell equivalent:
```bash
< infile ls -l | wc -l > outfile_shell
```

#### 3. Verification
Compare the outputs:
```bash
diff outfile_pipex outfile_shell
```
If `diff` produces no output, the files are identical.

#### 4. Error Handling
Test with non-existent files or invalid commands:
```bash
./pipex non_existent_file "ls -l" "wc -l" outfile
```
Check if it prints an error message (e.g., using `perror`) and handles the file descriptors correctly.

#### 5. Memory Leaks
Use Valgrind to ensure there are no memory leaks:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./pipex infile "ls -l" "wc -l" outfile
```

### Automated Testing
A tester script `tester.sh` is included to automate these checks.

1. Give execution permission:
   ```bash
   chmod +x tester.sh
   ```
2. Run the tester:
   ```bash
   ./tester.sh
   ```

The script checks standard behavior, multiple pipes (bonus), error handling, and memory leaks.
