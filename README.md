push_swap

A C program that sorts a random set of integers using two stacks (a and b) and a specific set of operations. The goal is to sort the numbers in ascending order using the minimum number of actions possible.

This project is part of the 42 School curriculum.
The Algorithm

I implemented the "Turk Algorithm" (or Mechanical Turk). Rather than using standard sorts like QuickSort or Radix (which are efficient in time but not in operation count), this greedy algorithm focuses on calculating the "cheapest" move for every node.

The logic flow:

    Push to B: Push all numbers from Stack A to Stack B, leaving only three elements in A.

        (Optimization: Pre-sort slightly by checking if a number is above/below the median to decide if it stays or rotates).

    Sort A: Quickly sort the remaining 3 numbers in Stack A.

    Calculate Costs: For every node in Stack B, calculate how many moves it takes to get it to the top of B, and how many moves to get its "target" (the closest larger number) to the top of A.

    Push Back: Execute the move set with the lowest cost (utilizing simultaneous rotations like rr and rrr to save moves) and push to A.

    Final Alignment: Rotate Stack A until the smallest number is at the top.

Operations

The program utilizes the standard 42 instruction set:

    sa, sb, ss: Swap the first two elements.

    pa, pb: Push the top element from one stack to another.

    ra, rb, rr: Rotate up (first becomes last).

    rra, rrb, rrr: Reverse rotate (last becomes first).

Installation

Clone the repository and compile using make.
Bash

git clone git@github.com:Xabieriribar/push_swap.git push_swap
cd push_swap
make

This will generate the push_swap executable. The project includes a custom libft which is compiled automatically.
Usage

Run the program by passing a list of integers as arguments.
Bash

./push_swap 2 1 3 6 5 8

You can also pass the numbers as a single string:
Bash

./push_swap "2 1 3 6 5 8"

Counting Operations

To check the efficiency (number of operations), you can pipe the output to wc -l:
Bash

ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l

Verification

If you have the 42 checker utility (usually provided in the subject), you can verify if the list is actually sorted:
Bash

ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_Mac $ARG

Should output: OK
Error Handling

The program handles various edge cases and returns Error on standard error if:

    Arguments contain non-numeric characters.

    Arguments exceed integer limits (INT_MAX / INT_MIN).

    Duplicate numbers are provided.

Project Structure

    push_swap.c: Main entry point and orchestration.

    parsing/: Input validation and array creation.

    operations/: The actual stack manipulation commands (sa, pb, rra, etc.).

    find_utils/: Logic for calculating move costs and finding target nodes.

    sort_utils/: Sorting logic for small sets (3 numbers) and the Turk algorithm controller.

    libft/: My custom C library.
