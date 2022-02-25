CC = gcc
ERROR_FLAGS = -Wall -Wextra
DEBUG_FLAGS = -g3 -fsanitize=address

stackk:
	$(CC) $(ERROR_FLAGS) main.c ./stack/stack.c -o a.out $(DEBUG_FLAGS)
	./a.out