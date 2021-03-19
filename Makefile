# DIRECTORIES
BIN_DIR := ./bin

LS_SRC_DIR := ./ls

# TARGET PROGRAMS
LS := $(BIN_DIR)/ls

# TARGET
PROGRAMS := $(LS)

# SOURCE FILES
LS_SRC_FILES := $(shell find $(LS_SRC_DIR) -name '*.c')

# PROGRAMS
CC := x86_64-los-gcc
CC_FLAGS := -g

# BASE RULES
all: dirs $(PROGRAMS)
	@echo "[ PROGRAMS ] Build Complete!"

install: all
	@mkdir -p ../sysroot/bin
	@cp -r $(BIN_DIR)/ ../sysroot/

clean:
	@rm -rf ../sysroot/bin/*
	@rm -rf $(BIN_DIR)/*
	@echo "[ PROGRAMS ] Cleaned!"

# COMPILATION RULES
.SECONDEXPANSION:

$(LS): $(LS_SRC_FILES)
	@echo "[ LS ] (CC) $@ . . ."
	@$(CC) $(CC_FLAGS) -o $@ $^

dirs:
	@mkdir -p $(BIN_DIR)

# . RULES
.PHONY: dirs