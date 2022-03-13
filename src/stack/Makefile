#### build flags
CC := gcc -std=c11
ERROR_FLAGS := -Wall -Wextra
SANITIZE := -g3 -fsanitize=address
MAKE_DEPENDENCE := -MD


#### files
BUILD_DIR := build
SOURCE_FILES := $(wildcard *.c)
OBJECT_FILES := $(addprefix $(BUILD_DIR)/,$(SOURCE_FILES:.c=.o))


#### build options
INCLUDE_PATH := . .. ../math_parser/
INCLUDE_FLAG := $(addprefix -I,$(INCLUDE_PATH))


#### include dependence file
-include $(BUILD_DIR)/*.d

#### targets
## build object files
$(BUILD_DIR)/%.o: %.c
	$(CC) $(INCLUDE_FLAG) $< -c -o $@ $(ERROR_FLAGS) $(SANITIZE) -MD

## build libstack.a target from object files
libstack.a: $(OBJECT_FILES)
	ar rc $@ $(OBJECT_FILES)
	ranlib $@


#### phony targets
.PHONY: clean all re

re: clean libstack.a

all: libstack.a

clean:
	find . -name "*.o" -print
	find . -name "*.a" -print
	find . -name "*.d" -print
