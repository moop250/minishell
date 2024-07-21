#!/bin/bash

error_count=0

# Function to run a test and increment error count if it fails
run_test() {
  if ! eval "$1"; then
    echo "Failed: $1" >&2
    ((error_count++))
  fi
}

# Export test variable
export TEST_VAR="test value"

# Create test directory and file
run_test "mkdir -p test_dir"
run_test "cd test_dir"
run_test "echo 'Test content' > test_file.txt"
run_test "[ -f test_file.txt ]"
run_test "[ '$(cat test_file.txt)' = 'Test content' ]"

# Test for middle number
middle_number=$(for i in {1..5}; do echo $i; done | sort -r | head -n 3 | tail -n 1)
echo "Middle number: $middle_number"
run_test "[ '$middle_number' = '3' ]"

# File counting
run_test "[ $(find . -type f -name '*.txt' | wc -l) -eq 1 ]"

# Process checking
run_test "ps aux | grep -v grep | grep -q '$$'"

# Command substitution
run_test "echo 'Command substitution: $(date +%Y-%m-%d)' | grep -q '$(date +%Y)'"

# Regular expression matching
run_test "[[ '${TEST_VAR}' =~ ^test\ v[a-z]+$ ]]"

# Trap handling
trap 'echo "Exit trap triggered"' EXIT

# Arithmetic operation
run_test "[ $(eval 'echo $((2**10))') -eq 1024 ]"

# Command existence checking
run_test "command -v ls >/dev/null 2>&1"

# Builtin command type checking
run_test "[ '$(type -t cd)' = 'builtin' ]"

# Shell option testing (nullglob)
shopt -s nullglob
run_test "echo *txt | grep -q 'test_file.txt'"

# Final error check and output
if [ $error_count -eq 0 ]; then
  echo "All tests passed" >&2
  exit 0
else
  echo "Test failed: $error_count error(s) occurred" >&2
  exit 1
fi