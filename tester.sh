#!/bin/bash

# ==============================================================================
#                               PIPEX TESTER
# ==============================================================================
# Usage: ./tester.sh
# Ensure you have valgrind installed for memory leak checks.

# Colors
GREEN="\033[1;32m"
RED="\033[1;31m"
BLUE="\033[1;34m"
YELLOW="\033[1;33m"
RESET="\033[0m"

PIPEX="./pipex"
INFILE="in_test.txt"
OUTFILE="out_test.txt"
EXPECTED="out_expected.txt"
LOGFILE="tester.log"

PASSED=0
FAILED=0

# ==============================================================================
#                               UTILS
# ==============================================================================

function cleanup {
    rm -f $INFILE $OUTFILE $EXPECTED "no_read_perm" "no_write_perm" "large_in"
}

function setup {
    cleanup
    # Standard input file
    echo "Lorem ipsum dolor sit amet" > $INFILE
    echo "consectetur adipiscing elit" >> $INFILE
    echo "42 Network" >> $INFILE
    echo "Pipex Project" >> $INFILE
    
    # Permission files
    touch "no_read_perm" && chmod 000 "no_read_perm"
    touch "no_write_perm" && chmod 000 "no_write_perm"
}

function print_result {
    local status=$1
    local name=$2
    local info=$3
    
    if [ "$status" == "OK" ]; then
        echo -e "${GREEN}[OK]${RESET} $name"
        ((PASSED++))
    else
        echo -e "${RED}[KO]${RESET} $name"
        [ ! -z "$info" ] && echo -e "${YELLOW}     $info${RESET}"
        ((FAILED++))
    fi
}

# ==============================================================================
#                               CORE TEST FUNCTION
# ==============================================================================

function run_test {
    local desc="$1"
    shift
    local args=("$@")
    
    local file1="${args[0]}"
    local file2="${args[${#args[@]}-1]}"
    
    # 1. Build Bash Command: < file1 cmd1 | cmd2 ... > file2
    local bash_cmd="< \"$file1\" ${args[1]}"
    for ((i=2; i<${#args[@]}-1; i++)); do
        bash_cmd="$bash_cmd | ${args[i]}"
    done
    bash_cmd="$bash_cmd > \"$EXPECTED\""
    
    # 2. Run Bash (Expected)
    eval "$bash_cmd" 2> /dev/null
    local expected_exit=$?
    
    # 3. Run Pipex (Actual)
    rm -f "$file2"
    $PIPEX "${args[@]}" > /dev/null 2> /dev/null
    local actual_exit=$?
    
    # 4. Compare
    diff "$EXPECTED" "$file2" > /dev/null 2>&1
    local diff_exit=$?
    
    if [ $diff_exit -eq 0 ]; then
        # Check if exit codes match in terms of success/failure (0 vs non-0)
        if ([ $expected_exit -eq 0 ] && [ $actual_exit -eq 0 ]) || ([ $expected_exit -ne 0 ] && [ $actual_exit -ne 0 ]); then
            print_result "OK" "$desc"
        else
            print_result "KO" "$desc" "Exit Code Mismatch (Bash: $expected_exit, Pipex: $actual_exit)"
        fi
    else
        print_result "KO" "$desc" "Output Differs"
    fi
}

function check_time {
    local desc="$1"
    local min_time="$2"
    shift 2
    local args=("$@")

    local start=$(date +%s)
    $PIPEX "${args[@]}" > /dev/null 2> /dev/null
    local end=$(date +%s)
    local duration=$((end - start))

    if [ $duration -ge $min_time ]; then
         print_result "OK" "$desc" "Duration: ${duration}s (Expected >= ${min_time}s)"
    else
         print_result "KO" "$desc" "Duration: ${duration}s (Expected >= ${min_time}s) - Did you wait for all children?"
    fi
}

function check_leaks {
    local desc="$1"
    shift
    
    if ! command -v valgrind &> /dev/null; then
        echo -e "${YELLOW}[SKIP] Valgrind not found${RESET}"
        return
    fi

    valgrind --leak-check=full --error-exitcode=42 --quiet $PIPEX "$@" > /dev/null 2>&1
    if [ $? -eq 42 ]; then
        echo -e "${RED}[LEAKS]${RESET} $desc"
        ((FAILED++))
    else
        echo -e "${GREEN}[CLEAN]${RESET} $desc"
        ((PASSED++))
    fi
}

# ==============================================================================
#                               EXECUTION
# ==============================================================================

echo -e "${BLUE}=== Compiling ===${RESET}"
make re > /dev/null
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed${RESET}"
    exit 1
fi
setup

echo -e "\n${BLUE}=== Mandatory Tests ===${RESET}"
run_test "Simple: ls -l | wc -l" "$INFILE" "ls -l" "wc -l" "$OUTFILE"
run_test "Grep: grep Pipex | wc -w" "$INFILE" "grep Pipex" "wc -w" "$OUTFILE"
run_test "Awk: awk | cat" "$INFILE" "awk {print\$1}" "cat" "$OUTFILE"
run_test "Abs Path: /bin/ls | /usr/bin/wc" "$INFILE" "/bin/ls" "/usr/bin/wc -l" "$OUTFILE"

echo -e "\n${BLUE}=== Error Handling ===${RESET}"
run_test "Input: Non-existent file" "ghost_file" "ls -l" "wc -l" "$OUTFILE"
run_test "Input: Permission denied" "no_read_perm" "ls -l" "wc -l" "$OUTFILE"
run_test "Cmd: First cmd invalid" "$INFILE" "wrong_cmd" "wc -l" "$OUTFILE"
run_test "Cmd: Second cmd invalid" "$INFILE" "ls -l" "wrong_cmd" "$OUTFILE"

# Output permission test is special (bash handles redirection before execution)
echo -e "${YELLOW}Testing Output Permission Denied...${RESET}"
$PIPEX "$INFILE" "ls -l" "wc -l" "no_write_perm" 2> /dev/null
if [ $? -ne 0 ]; then
    echo -e "${GREEN}[OK]${RESET} Output Perms"
    ((PASSED++))
else
    echo -e "${RED}[KO]${RESET} Output Perms (Should fail)"
    ((FAILED++))
fi

echo -e "\n${BLUE}=== Argument Checks ===${RESET}"
$PIPEX "$INFILE" "ls -l" "$OUTFILE" > /dev/null 2>&1
if [ $? -ne 0 ]; then
    print_result "OK" "Too few args (3 args)"
else
    print_result "KO" "Too few args (3 args) - Should fail/exit non-zero"
fi


echo -e "\n${BLUE}=== Bonus: Multiple Pipes ===${RESET}"
run_test "3 Cmds: ls | grep | wc" "$INFILE" "ls -l" "grep Pipex" "wc -l" "$OUTFILE"
run_test "4 Cmds: cat | cat | grep | wc" "$INFILE" "cat" "cat" "grep Pipex" "wc -l" "$OUTFILE"
run_test "Complex: sed | tr | awk" "$INFILE" "sed s/Pipex/42/g" "tr a-z A-Z" "awk {print\$1}" "$OUTFILE"

echo -e "\n${BLUE}=== Edge Cases ===${RESET}"
# Large file test
yes "Lines" | head -n 10000 > large_in
run_test "Large Input (10k lines)" "large_in" "cat" "wc -l" "$OUTFILE"

# Unset PATH test
echo -e "${YELLOW}Testing unset PATH (Absolute paths should still work)...${RESET}"
(unset PATH; $PIPEX "$INFILE" "/bin/ls" "/usr/bin/wc -l" "$OUTFILE") > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[OK]${RESET} Unset PATH"
    ((PASSED++))
else
    echo -e "${RED}[KO]${RESET} Unset PATH failed"
    ((FAILED++))
fi

echo -e "\n${BLUE}=== Timing/Wait Tests ===${RESET}"
# Mandatory: sleep 3 | sleep 1 -> Should take 3 seconds if waiting for all.
# If you only wait for the last one (sleep 1), it will take 1 second (FAIL).
check_time "Mandatory: sleep 3 | sleep 1" 3 "$INFILE" "sleep 3" "sleep 1" "$OUTFILE"

# Bonus: sleep 1 | sleep 5 | sleep 2 -> Should take 5 seconds.
check_time "Bonus: sleep 1 | sleep 5 | sleep 2" 5 "$INFILE" "sleep 1" "sleep 5" "sleep 2" "$OUTFILE"

echo -e "\n${BLUE}=== Memory Leaks (Valgrind) ===${RESET}"
check_leaks "Mandatory: ls | wc" "$INFILE" "ls -l" "wc -l" "$OUTFILE"
check_leaks "Bonus: cat | grep | wc" "$INFILE" "cat" "grep Pipex" "wc -l" "$OUTFILE"
check_leaks "Error: Bad command" "$INFILE" "badcmd" "wc -l" "$OUTFILE"

# Cleanup
cleanup
make fclean > /dev/null
rm -f tester.log

echo -e "\n${BLUE}=== Summary ===${RESET}"
echo -e "Passed: ${GREEN}$PASSED${RESET}"
echo -e "Failed: ${RED}$FAILED${RESET}"

if [ $FAILED -eq 0 ]; then
    exit 0
else
    exit 1
fi