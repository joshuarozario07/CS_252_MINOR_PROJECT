# CS252_Project

# About the Project

These are projects from the textbook Operating Systems Concepts (9th edition) by ABRAHAM SILBERSCHATZ PETER BAER GALVIN GREG GAGNE

Thess projects were assigned as part of the final project for our Operating Systems course (CS 252) taught at National Institute of Technology Karnataka, Odd semester of 2022.

Done by

Sreedev Sreekumar https://github.com/SreeDev-4522

Joshua Rozario Raymond https://github.com/joshuarozario07

This repository has implementation of two different projects:

1) Sudoku Validator 

2) UNIX Shell & History Feature

Each have been assigned a specific folder with all the required files within their respective folder

# PROJECT 1 : Sudoku_Solution_Validator

# Description:

This project involves implementing of multithreading concept.

The solution involves takeing a Sudoku puzzle solution as an input and then determines whether the puzzle solution is valid. This validation is done using both single thread and 27 threads.
 
The 27 threads are created as follows:
 
9 for each 3x3 subsection
 
9 for the 9 columns
 
9 for the 9 rows.
 
Each thread returns a integer value of 1 indicating that the corresponding region in the puzzle they were responsible for is valid.
The program then waits for all threads to complete their execution and checks if the return values of all the threads have been set to 1.
 
If yes, the solution is valid. If not, solution is invalid.

This program also displays the total time taken for validation.

## How to Execute

A Linus, UNIX or MAC OS X system is required for execution.

Sudoku_validator.cpp needs to be run.

# PROJECT 2 : Unix Shell and History Feature

# Description:

This project consists of designing a C Program to serve as a shell interface that accepts user commands and then executes each command in a separate process by using the fork() system call and is executed using one of the system calls in the exec() family. . 
This project can executed on any Linux, UNIX, or Mac OS X system. 
A shell interface gives the user a prompt, after which the next command is entered. 
In UNIX shells, the child process is allowed to run in the background, or concurrently and to accomplish this, we add an ampersand ( & ) at the end of the command. 

The main() function presents the prompt osh-> and outlines the steps to be taken after input from the user has been read. 
The main() function continually loops as long as should run equals 1; when the user enters exit at the prompt, the program will set run to 0 and terminate.

## How to Execute

1. A Linux, UNIX or Mac OS X system is required for execution. 
2. Hist.c has to be run. 

## Credits

###Sudoku_Solution_Validator

This project folder was taken from the github repo "https://gist.github.com/sowmyagowri/f4bde25b3ebba1e6e9930afbdf31a25b". 

All credits to  Sowmya Gowrishankar (sowmyagowri)

###Unix Shell and History Feature

Used StackOverflow, GFG and guides to design and implement the Unix Shell and its functioning. 
