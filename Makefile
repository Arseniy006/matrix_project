CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
LDFLAGS = -lm
TEST_LDFLAGS = -lcunit

SRC = src/main.c src/matrix/matrix.c
OBJ = $(SRC:.c=.o)
EXEC = build/matrix_program

TEST_SRC = tests/test_matrix.c src/matrix/matrix.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_EXEC = build/test_matrix

all: $(EXEC)

test: $(TEST_EXEC)

$(EXEC): $(OBJ)
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_EXEC): $(TEST_OBJ)
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(TEST_LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(EXEC) $(TEST_EXEC)

.PHONY: all test clean
