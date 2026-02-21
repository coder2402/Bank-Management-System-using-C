CC = gcc
CFLAGS = -Wall -Wextra -I. -O2
LDFLAGS = -lm

# Source files
MAIN_SRC = Bank_Management_system.c
LIB_SRC = interest.c
TEST_SRC = tests/test_interest.c

# Object files
LIB_OBJ = interest.o

# Targets
APP_BIN = Bank_Management_system
TEST_BIN = tests/test_interest

.PHONY: all clean test

all: $(APP_BIN) $(TEST_BIN)

$(APP_BIN): $(MAIN_SRC) $(LIB_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_BIN): $(TEST_SRC) $(LIB_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(LIB_OBJ): $(LIB_SRC) interest.h
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(APP_BIN) $(TEST_BIN) $(LIB_OBJ)
