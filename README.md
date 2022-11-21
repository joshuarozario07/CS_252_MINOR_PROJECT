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
 
