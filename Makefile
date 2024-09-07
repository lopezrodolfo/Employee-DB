CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11

RF_LIB = readfile.o
TESTER_DEPS = employee_db.c $(RF_LIB)

TARGETS = employee_db 

all: $(TARGETS)

employee_db: main.c employee_db.c $(RF_LIB)
	$(CC) $(CFLAGS) -o $@ $^

$(RF_LIB): readfile.c readfile.h
	$(CC) $(CFLAGS) -c readfile.c

clean:
	$(RM) $(TARGETS) *.o *.so
