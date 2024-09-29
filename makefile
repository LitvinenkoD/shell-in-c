CC = gcc
CFLAGS = -Iinclude -Wall
OBJ = main.o file_input_processing.o utils.o text_producers.o buffer_utils.o core_functions.o wildcard_processer.o core_utils.o ArrayList.o
EXEC = mysh
MEMFLAGS = --leak-check=full --show-leak-kinds=all

%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)


all: $(EXEC) tester test

mysh: $(OBJ)
	$(CC) -o $@ $^
	chmod +x $@

tester: testrunner.c
	$(CC) -o $@ $^

test: test.c
	gcc -o test test.c

memcheck: $(EXEC)
	valgrind $(MEMFLAGS) ./$(EXEC)

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: clean memcheck