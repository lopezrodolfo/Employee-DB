# Employee Database Program

A simple command-line application to manage employee records.

## Author

Rodolfo Lopez

## Date

September 24, 2020

## Features

- Add new employees
- View all employees
- Search for employees by ID
- Search for employees by Last Name

## Requirements

- C compiler (e.g., GCC)
- Make

## Project Structure

- `main.c`: The entry point of the program, containing the main menu and user interaction logic.
- `employee.h`: Header file defining the Employee struct and function prototypes.
- `employee.c`: Implementation of employee-related functions (add, view, search).
- `file_operations.h`: Header file for file I/O function prototypes.
- `file_operations.c`: Implementation of file reading and writing functions.
- `Makefile`: Compilation instructions for building the project.

## Compilation and Usage

1. Clone the repository
2. Compile the program:
   ```
   make
   ```
3. Run the program:
   ```
   ./employee_db small_db.txt
   ```
   or
   ```
   ./employee_db full_db.txt
   ```

## Acknowledgements

Professor Sat Garcia wrote the starter code and I implemented the functions in employee_db.c
