#### build flags
CC := gcc -std=c11
ERROR_FLAGS := -Wall -Wextra
SANITIZE := -g3 -fsanitize=address
MAKE_DEPENDENCE := -MD
MATH_LIB := -lm


#### files
BUILD_DIR := build
SOURCE_FILES := $(filter-out main.c, $(wildcard *.c))
OBJECT_FILES := $(addprefix $(BUILD_DIR)/,$(SOURCE_FILES:.c=.o))

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
	$(CC) $(INCLUDE_FLAG) $< -c -o $@ $(ERROR_FLAGS) $(SANITIZE) -MD $(MATH_LIB)

## build libstack.a target from object files
libmathparser.a: $(OBJECT_FILES)
	ar rc $@ $(OBJECT_FILES)
	ar rc $@
	ranlib $@


#### phony targets
.PHONY: clean all re clear

re: clean libstack.a

all: libmathparser.a

clean:
	find . -name "*.out" -delete
	find . -name "*.o" -delete
	find . -name "*.a" -delete
	find . -name "*.d" -delete

clear:
	clear

#### extra targets
fprog: clear libmathparser.a libstack.a
	$(CC) $(INCLUDE_FLAG) $(ERROR_FLAGS) $(SANITIZE) main.c libmathparser.a libstack.a -o main.out $(MATH_LIB)
	./main.out
