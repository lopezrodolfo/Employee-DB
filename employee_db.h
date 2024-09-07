#ifndef _EMPLOYEEDB_H_
#define _EMPLOYEEDB_H_
/*
 * Header file that defines our Employee DB's structs and declares functions to
 * be used by our application.
 *
 * Note: Having a separate module for the main function and everything else will
 * allow us to write automated tests for our functions.
 */

// Global constant definitions
#define MAXNAME 25
#define MAXFILENAME 128
#define MAXEMPLOYEE	1024

/**
 * A simple representation of an employee.
 */
struct Employee {
	char first_name[MAXNAME];
	char last_name[MAXNAME];
	int id;
	int salary;
};

// The following line allows us to use "Employee" rather than 
// "struct Employee" throughout this code.
typedef struct Employee Employee;


/**
 *  This function gets the filename passed in as a command line option
 *  and copies it into the filename parameter. It exits with an error 
 *  message if the command line is badly formed.
 *
 *  @param filename The string to fill with the passed filename.
 *  @param argc The number of command line arguments.
 *  @param argv The actual command line parameters.
 */
void parse_filename(char filename[], int argc, char *argv[]);

/**
 * Reads employee data from a file with the given filename, adding them into the
 * given list of employees.
 *
 * @note You may assume there will never be more than MAXEMPLOYEE employees in
 * the given file.
 *
 * @param filename The name of the file with the employee data.
 * @param employees An array where employee data will be stored. The function
 *   will overwrite the original contents of this array.
 *
 * @return The number of employees added to the list.
 */
int read_employees_from_file(char *filename, Employee employees[]);

/**
 * Prints menu of options and prompts user to enter a selection.
 * If the user enters an invalid selection, they should be reprompted.
 *
 * @return The user's validated selection.
 */
int get_menu_selection();

/**
 * Prints a nicely formatted version of the employee list.
 *
 * @param e The employee to print.
 */
void print_employee(Employee e);

/**
 * Prints a nicely formatted version of the employee list.
 *
 * @param employees The list of employees.
 * @param num_employees The number of employees in the list.
 */
void print_db(Employee employees[], int num_employees);

/**
 * Inserts the given employee into the array of employees.
 * The index where the employee is inserted will be based on their ID number to
 * ensure the employees remain sorted by ID.
 *
 * @param employees The list of employees.
 * @param num_employees The number of employees in the list.
 * @param new_employee The employee to add.
 */
void insert_employee(Employee employees[], int num_employees, Employee new_employee);

/**
 * Prompts user to enter data for a new employee and then adds that user to the
 * list of employees.
 *
 * @note The user may decide they don't want to add an employee so this function
 * doesn't guarantee a new user will be added to the list. The return value will
 * indicate whether a new employee was added or not.
 *
 * @param employees The list of employees.
 * @param num_employees The number of employees in the list.
 *
 * @return True (i.e. 1) if a user was added, False (0) otherwise.
 */
int add_employee(Employee employees[], int num_employees);

/**
 * Prompts the user for an employee ID and looks up the corresponding employee
 * in the database. If found, prints the employee's information.
 *
 * @param employees The list of employees.
 * @param num_employees The number of employees in the list.
 */
void lookup_by_id(Employee employees[], int num_employees);

/**
 * Prompts the user for a last name and looks up all employees with that last name
 * in the database. Prints the information for all matching employees.
 *
 * @param employees The list of employees.
 * @param num_employees The number of employees in the list.
 */
void lookup_by_last_name(Employee employees[], int num_employees);

#endif