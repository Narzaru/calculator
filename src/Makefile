CC = gcc -std=c11
ERROR_FLAGS = -Wall -Wextra
DEBUG_FLAGS = -g -fsanitize=address

math_parser.a:
	make -C ./math_parser/ math_parser.a
	cp ./math_parser/math_parser.a .

linter:
	cp ../materials/linters/CPPLINT.cfg .
	find . -name "*.c" -exec python3 ../materials/linters/cpplint.py {} \;
	find . -name "*.h" -exec python3 ../materials/linters/cpplint.py {} \;
	rm -f CPPLINT.cfg

libstack.a:
	make -C ./stack/ libstack.a
	cp ./stack/libstack.a .

calculator.out: clean math_parser.a libstack.a
	$(CC) `pkg-config --cflags gtk+-3.0` main.c plotter/plotter.c callbacks.c -o $@ $(ERROR_FLAGS) $(DEBUG_FLAGS) `pkg-config --libs gtk+-3.0` -rdynamic -lm -Imath_parser/ -I. -Iplotter/ math_parser.a libstack.a
	./$@

clean:
	find . -name "*.o" -delete
	find . -name "*.out" -delete
	find . -name "*.a" -delete
	find . -name "*.d" -delete
