CC := gcc -std=c11
ERROR_FLAGS := -Wall -Wextra
DEBUG_FLAGS := -g -fsanitize=address
MATH_LIB := -lm
FOLDERS := src src/math_parser src/math_parser/build src/plotter src/stack src/stack/build src/ui

#### build options
INCLUDE_PATH := . math_parser/ stack/ plotter/
INCLUDE_FLAG := $(addprefix -I,$(INCLUDE_PATH))

libmathparser.a:
	make -C ./math_parser/ libmathparser.a
	cp ./math_parser/libmathparser.a .

libstack.a:
	make -C ./stack/ libstack.a
	cp ./stack/libstack.a .

calculator.out: clean libmathparser.a libstack.a
	$(CC) `pkg-config --cflags gtk+-3.0` main.c gtk_help.c callbacks/calculator.c callbacks/grapher.c simple_grapher/grapher.c -o $@ $(ERROR_FLAGS) $(DEBUG_FLAGS) $(MATH_LIB) `pkg-config --libs gtk+-3.0` $(INCLUDE_FLAG) -rdynamic libmathparser.a libstack.a
	./$@

all: calculator.out

dist:
	for dir in $(FOLDERS); \
	do \
		if [ ! -d $$dir ]; \
		then \
			mkdir $$dir; \
		else \
			echo "$$dir is exist"; \
		fi; \
	done;

	cp math_parser/*.c src/math_parser
	cp math_parser/*.h src/math_parser
	cp math_parser/Makefile src/math_parser

	cp stack/*.c src/stack
	cp stack/*.h src/stack
	cp stack/Makefile src/stack

	cp plotter/*.c src/plotter
	cp plotter/*.h src/plotter

	cp ui/*.ui src/ui

	cp *.c src
	cp *.h src
	cp Makefile src

	tar -zcf src.tar src
	gzip src.tar

install: calculator.out

unistall:
	rm -f calculator.out

.PHONY: clean linter install unsitall all

clean:
	find . -name "*.o" -delete
	find . -name "*.out" -delete
	find . -name "*.a" -delete
	find . -name "*.d" -delete
	find . -name "*.gz" -delete

linter:
	cp ../materials/linters/CPPLINT.cfg .
	find . -name "*.c" -exec python3 ../materials/linters/cpplint.py {} \;
	find . -name "*.h" -exec python3 ../materials/linters/cpplint.py {} \;
	rm -f CPPLINT.cfg
