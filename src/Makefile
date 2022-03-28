CC := gcc -std=c11
ERROR_FLAGS := -Wall -Wextra
DEBUG_FLAGS := -g -fsanitize=address
MATH_LIB := -lm

BUILD_FOLDER := build
SOURCE_FILES := $(wildcard *.c)
SOURCE_FILES += $(wildcard callbacks/*.c)
OBJECT_FILES := $(addprefix $(BUILD_FOLDER)/,$(SOURCE_FILES:.c=.o))

PROJECT_ROOT_FOLDER := src
PROJECT_FOLDERS := \
	$(PROJECT_ROOT_FOLDER) \
	$(PROJECT_ROOT_FOLDER)/math_parser \
	$(PROJECT_ROOT_FOLDER)/math_parser/build \
	$(PROJECT_ROOT_FOLDER)/simple_grapher \
	$(PROJECT_ROOT_FOLDER)/simple_grapher/build \
	$(PROJECT_ROOT_FOLDER)/stack \
	$(PROJECT_ROOT_FOLDER)/stack/build \
	$(PROJECT_ROOT_FOLDER)/ui

#### build options
INCLUDE_PATH := . math_parser stack simple_grapher
INCLUDE_FLAG := $(addprefix -I,$(INCLUDE_PATH))

$(BUILD_FOLDER)/libmathparser.a:
	make -C ./math_parser/ libmathparser.a
	cp ./math_parser/libmathparser.a ./build/

$(BUILD_FOLDER)/libstack.a:
	make -C ./stack/ libstack.a
	cp ./stack/libstack.a ./build/

$(BUILD_FOLDER)/libgrapher.a:
	make -C ./simple_grapher libgrapher.a
	cp ./simple_grapher/libgrapher.a ./build/

$(BUILD_FOLDER)/%.o: %.c
	$(CC) $(INCLUDE_FLAG) $< -c -o $@ $(ERROR_FLAGS) $(SANITIZE) -MD $(MATH_LIB) `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

calculator: $(OBJECT_FILES) $(BUILD_FOLDER)/libmathparser.a $(BUILD_FOLDER)/libstack.a $(BUILD_FOLDER)/libgrapher.a
	$(CC) `pkg-config --cflags gtk+-3.0` -o $@ $(ERROR_FLAGS) $(DEBUG_FLAGS) $(MATH_LIB) `pkg-config --libs gtk+-3.0` $(INCLUDE_FLAG) -rdynamic $^

all: calculator gcov_report

install: calculator
	cp ./calculator ../program
	cp -r ./ui ../program

unistall:
	rm -rf ../program/*

clean:
	make -C ./math_parser/ clean
	make -C ./stack/ clean
	make -C ./simple_grapher clean
	find . -name "*.o" -delete
	find . -name "*.a" -delete
	find . -name "*.d" -delete
	find . -name "*.gz" -delete
	find . -name "*.tar" -delete
	rm -rf src	
	rm -f calculator

dist:
	for dir in $(PROJECT_FOLDERS); \
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

	cp simple_grapher/*.c src/simple_grapher
	cp simple_grapher/*.h src/simple_grapher
	cp simple_grapher/Makefile src/simple_grapher

	cp ui/*.ui src/ui

	cp *.c src
	cp *.h src
	cp Makefile src

	tar -zcf src.tar src
	gzip src.tar

	rm -rf src

tests:
	make -C ./math_parser/ test.out
	./math_parser/test.out

gcov_report: tests
	make -C ./math_parser/ gcov_report
	open ./math_parser/gcov_report/index.html

.PHONY: clean linter install unsitall all tests gcov_report

linter:
	cp ../materials/linters/CPPLINT.cfg .
	find . -name "*.c" -exec python3 ../materials/linters/cpplint.py {} \;
	find . -name "*.h" -exec python3 ../materials/linters/cpplint.py {} \;
	rm -f CPPLINT.cfg
