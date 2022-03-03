CC = gcc -std=c11
ERROR_FLAGS = -Wall -Wextra
DEBUG_FLAGS = -g -fsanitize=address

libstack.a:
	make -C ./stack/ libstack.a
	cp ./stack/libstack.a .

calculator.out: clean
	$(CC) `pkg-config --cflags gtk+-3.0` main.c plotter/plotter.c callbacks.c -o $@ $(ERROR_FLAGS) $(DEBUG_FLAGS) `pkg-config --libs gtk+-3.0` -rdynamic -lm
	./$@

clean:
	find . -name "*.o" -delete
	find . -name "*.out" -delete
	find . -name "*.a" -delete
	find . -name "*.d" -delete
