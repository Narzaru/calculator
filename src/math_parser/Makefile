#### build flags
CC := gcc -std=c11
ERROR_FLAGS := -Wall -Wextra
SANITIZE := -g3 -fsanitize=address
MAKE_DEPENDENCE := -MD
MATH_LIB := -lm
CHECK_LIB := -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
COVERAGE_FLAG := -fprofile-arcs -ftest-coverage

#### files
BUILD_DIR := build
BUILD_DIR_TEST := $(BUILD_DIR)/test
SOURCE_FILES := $(filter-out main.c, $(wildcard *.c))
OBJECT_FILES := $(addprefix $(BUILD_DIR)/,$(SOURCE_FILES:.c=.o))
OBJECT_TEST_FILES := $(addprefix $(BUILD_DIR_TEST)/,$(SOURCE_FILES:.c=.o))

#### build options
INCLUDE_PATH := . .. ../stack/
INCLUDE_FLAG := $(addprefix -I,$(INCLUDE_PATH))

#### include dependence file
-include $(BUILD_DIR)/*.d

#### targets
## build stack library
libstack.a:
	make -C ../stack/ libstack.a
	cp ../stack/libstack.a .

## build object files
$(BUILD_DIR)/%.o: %.c
	$(CC) $(INCLUDE_FLAG) $< -c -o $@ $(ERROR_FLAGS) $(SANITIZE) -MD $(MATH_LIB) `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`


## build object files for tests and coverage
$(BUILD_DIR_TEST)/%.o: %.c
	$(CC) $(COVERAGE_FLAG) $(INCLUDE_FLAG) -c $< -o $@ $(ERROR_FLAGS) $(SANITIZE) -MD $(MATH_LIB) `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

## build libmathparser.a target from object files
libmathparser.a: $(OBJECT_FILES)
	ar rc $@ $(OBJECT_FILES)
	ar rc $@
	ranlib $@

## build test
test.out: ./tests/tests.c $(OBJECT_TEST_FILES) libstack.a
	$(CC) $(COVERAGE_FLAG) $(INCLUDE_FLAG) ./tests/tests.c $(OBJECT_TEST_FILES) libstack.a -o $@ $(ERROR_FLAGS) $(SANITIZE) -MD $(MATH_LIB) $(CHECK_LIB)

## gcov report target
gcov_report: test.out
	./$<
	lcov -t "$<" -o gcovreport.info -c -d build/test
	genhtml -o $@ gcovreport.info
#	open gcov_report/index.html


#### phony targets
.PHONY: clean all re clear

re: clean libstack.a

all: libmathparser.a

clean:
	find . -name "*.out" -delete
	find . -name "*.o" -delete
	find . -name "*.a" -delete
	find . -name "*.d" -delete
	find . -name "*gcno" -delete
	find . -name "*gcda" -delete
	rm -rf gcov_report
	rm -rf gcovreport.info

clear:
	clear
