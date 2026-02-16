CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

all: test_interest Bank_Management_system

interest.o: interest.c interest.h
	$(CC) $(CFLAGS) -c interest.c

test_interest: test_interest.c interest.o
	$(CC) $(CFLAGS) test_interest.c interest.o -o test_interest $(LDFLAGS)

Bank_Management_system: Bank_Management_system.c interest.o
	$(CC) $(CFLAGS) Bank_Management_system.c interest.o -o Bank_Management_system $(LDFLAGS)

test: test_interest
	./test_interest

clean:
	rm -f *.o test_interest Bank_Management_system record.dat
