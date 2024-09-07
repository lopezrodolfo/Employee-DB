/**
 * Employee database program.
 */

#include <stdlib.h>
#include <stdio.h>

#include "readfile.h"
#include "employee_db.h"

// forward declaration of functions
void read_and_print(char *filename);

int main(int argc, char *argv[]) {

	// This initializes the filename string from the command line arguments
	char filename[MAXFILENAME];
	parse_filename(filename, argc, argv);

	Employee employees[MAXEMPLOYEE];
	int num_employees = read_employees_from_file(filename, employees);

	int done = 0;
	while (done == 0) {
		int selection = get_menu_selection();

		if (selection == 1) {
			// Print the employee DB
			print_db(employees, num_employees);
		}
		else if (selection == 2) {
			// Lookup an employee by ID
			lookup_by_id(employees, num_employees);
		}
		else if (selection == 3) {
			// Lookup an employee by Last Name
			lookup_by_last_name(employees, num_employees);
		}
		else if (selection == 4) {
			// Add an employee to the DB
			int added = add_employee(employees, num_employees);
			num_employees += added;
		}
		else {
			// Exit the program
			done = 1;
		}
	}

	printf("\nGood bye\n");
	return 0;
}