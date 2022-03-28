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

## build object files
$(BUILD_DIR)/%.o: %.c
	$(CC) $(INCLUDE_FLAG) $< -c -o $@ $(ERROR_FLAGS) $(SANITIZE) -MD $(MATH_LIB) `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`


## build libgrapher.a target from object files
libgrapher.a: $(OBJECT_FILES)
	ar rc $@ $(OBJECT_FILES)
	ar rc $@
	ranlib $@

#### phony targets
.PHONY: clean all re clear

re: clean libgrapher.a

all: libgrapher.a

clean:
	find . -name "*.o" -delete
	find . -name "*.a" -delete
	find . -name "*.d" -delete

clear:
	clear
