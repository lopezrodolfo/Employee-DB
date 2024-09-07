/**
 * Employee DB functions are implemented for COMP280 Project 1.
 *
 * @author Rodolfo Lopez
 */

#include <stdio.h>  // the C standard I/O library
#include <stdlib.h> // the C standard library
#include <string.h> // the C string library


// Include headers that are unique to this program
#include "readfile.h"  // file reading routines
#include "employee_db.h" // DB program functions


int read_employees_from_file(char *filename, Employee employees[]) {
	printf("Initializing employee database from file: '%s'\n\n", filename);

	int ret = open_file(filename);  
	if (ret == -1) {
		printf("Unable to open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	Employee new_employee;
	int num_employees = 0;

	while (ret != -1) {    
		ret = read_int(&new_employee.id);
		if (ret) { break; }

		ret = read_string(new_employee.first_name);
		if (ret) { break; }

		ret = read_string(new_employee.last_name);
		if (ret) { break; }

		ret = read_int(&new_employee.salary);

		insert_employee(employees, num_employees, new_employee);
		num_employees++;
	}


	close_file();  

	return num_employees;
}

int get_menu_selection() {
	printf("\n\nEmployee DB Menu:\n");
	printf("-----------------------------------\n");
	printf("  (1) Print the Database.\n");
	printf("  (2) Lookup by ID.\n");
	printf("  (3) Lookup by Last Name.\n");
	printf("  (4) Add an Employee.\n");
	printf("  (5) Quit.\n");
	printf("-----------------------------------\n");

	int choice = 0;
	int done = 0;
	while (!done) {
		printf("Enter your selection (1-5): ");
		scanf("%d", &choice);
		if (choice < 1 || choice > 5) {
			printf("\nInvalid selection (%d). Valid selections are 1 through 5.\n", choice);
		}
		else {
			done = 1;
		}
	}

	return choice;
}


void print_employee(Employee e) {
	printf("%-25s %-25s %7d  %6d\n", e.first_name, e.last_name, e.salary, e.id);
}

void print_db(Employee employees[], int num_employees) {
	printf("\n%-25s %-25s %7s   %s\n", "FIRST NAME", "LAST NAME", "SALARY", "ID");
	printf("--------------------------------------------------------------------\n");
	for (int i = 0; i < num_employees; i++) {
		print_employee(employees[i]);
	}
	printf("--------------------------------------------------------------------\n");
	printf("Number of employees: (%d)\n", num_employees);
}


void insert_employee(Employee employees[], int num_employees, Employee new_employee) {
    // Find the correct insertion index
    int insertion_index = num_employees; // default to the end of the array
    for (int i = 0; i < num_employees; i++) {
        if (new_employee.id < employees[i].id) {
            insertion_index = i;
            break;
        }
    }

    // Shift employees to make space for the new employee
    for (int i = num_employees; i > insertion_index; i--) {
        employees[i] = employees[i - 1];
    }

    // Insert the new employee
    employees[insertion_index] = new_employee;
}



int add_employee(Employee employees[], int num_employees) {
	Employee new_employee;

	printf("Enter the new employee's FIRST NAME: ");
	scanf("%s", new_employee.first_name);
	printf("Enter the new employee's LAST NAME: ");
	scanf("%s", new_employee.last_name);

	int valid = 0;

	while (!valid) {
		printf("Enter the new employee's ID (100000-999999): ");
		scanf("%d", &new_employee.id);

		if (new_employee.id < 100000 || new_employee.id > 999999) {
			printf("\nInvalid ID (%d). Valid IDs are between 100000 and 999999.\n", new_employee.id);
		}
		else {
			int is_duplicate = 0;
			for (int i = 0; i < num_employees; i++) {
				if (new_employee.id == employees[i].id) {
					printf("\nInvalid ID (%d). This ID is already in use by another employee.\n", 
							new_employee.id);
					is_duplicate = 1;
					break;
				}
			}

			if (!is_duplicate) {
				valid = 1;
			}
		}
	}

	valid = 0;

	while (!valid) {
		printf("Enter the new employee's SALARY (1-1000000): ");
		scanf("%d", &new_employee.salary);

		if (new_employee.salary < 1 || new_employee.salary > 1000000) {
			printf("\nInvalid Salary ($%d). Valid salaries are 1 to 1000000.\n", new_employee.salary);
		}
		else {
			valid = 1;
		}
	}

	printf("\nHere is the new employee's data:\n\n");
	printf("\tFirst Name: %s\n", new_employee.first_name);
	printf("\tLast Name: %s\n", new_employee.last_name);
	printf("\tID: %d\n", new_employee.id);
	printf("\tSalary: $%d\n", new_employee.salary);

	valid = 0;
	char response[10];

	while (1) {
		printf("Would you like to add this employee to the database (yes/no)? ");
		scanf("%s", response);

		if (strncmp(response, "no", 10) == 0) {
			printf("New employee was NOT added.\n");
			return 0;
		}
		else if (strncmp(response, "yes", 10) == 0) {
			insert_employee(employees, num_employees, new_employee);
			printf("\nNew employee was successfully added.\n");
			return 1;
		}
		else {
			printf("\nInvalid response. Please enter yes or no.\n");
		}
	}

}


void lookup_by_id(Employee employees[], int num_employees) {

	printf("Enter an Employee ID (100000-999999): ");

	int id = 0;
	scanf("%d", &id);
	if (id < 100000 || id > 999999) {
		printf("\nInvalid ID (%d). Valid IDs are between 100000 and 999999.", id);
		return;
	}

	for (int i = 0; i < num_employees; i++) {
		if (employees[i].id == id) {
			printf("\n%-25s %-25s  %7s  %s\n", "FIRST NAME", "LAST NAME", "SALARY", "ID");
			printf("--------------------------------------------------------------------\n");
			print_employee(employees[i]);
			return;
		}
	}

	printf("\nAn employee with ID %d does not exist.\n", id);
}


void lookup_by_last_name(Employee employees[], int num_employees) {
	printf("Enter an Employee's Last Name: ");

	char last_name[MAXNAME];
	scanf("%s", last_name);


	int has_match = 0;
	for (int i = 0; i < num_employees; i++) {
		if (strncmp(employees[i].last_name, last_name, MAXNAME) == 0) {
			if (!has_match) {
				printf("\n%-25s %-25s  %7s  %s\n", "FIRST NAME", "LAST NAME", "SALARY", "ID");
				printf("--------------------------------------------------------------------\n");
				has_match = 1;
			}
			print_employee(employees[i]);
		}
	}

	if (!has_match) {
		printf("\nAn employee with last name %s does is not in the database.\n", last_name);
	}
}

// DO NOT MODIFY ANY OF THE CODE BELOW THIS POINT!!!

void parse_filename(char filename[], int argc, char *argv[]) {

	if (argc != 2) {
		printf("Usage: %s database_file\n", argv[0]);
		// exit function: quits the program immediately...some errors are not 
		// recoverable by the program, so exiting with an error message is 
		// reasonable error handling option in this case
		exit(1);   
	}
	if (strlen(argv[1]) >= MAXFILENAME) { 
		printf("Filename, %s, is too long, cp to shorter name and try again\n",
				filename);
		exit(1);
	}
	strcpy(filename, argv[1]);
}