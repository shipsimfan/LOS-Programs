# DIRECTORIES
BIN_DIR := ./bin

CAT_SRC_DIR := ./cat
LS_SRC_DIR := ./ls
TRUNCATE_SRC_DIR := ./truncate

# TARGET PROGRAMS
CAT := $(BIN_DIR)/cat
LS := $(BIN_DIR)/ls
TRUNCATE := $(BIN_DIR)/truncate

# TARGET
PROGRAMS := $(CAT) $(LS) $(TRUNCATE)

# SOURCE FILES
CAT_SRC_FILES := $(shell find $(CAT_SRC_DIR) -name '*.c')
LS_SRC_FILES := $(shell find $(LS_SRC_DIR) -name '*.c')
TRUNCATE_SRC_FILES := $(shell find $(TRUNCATE_SRC_DIR) -name '*.c')

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

$(CAT): $(CAT_SRC_FILES)
	@echo "[ PROGRAMS ][ CAT ] (CC) $@ . . . "
	@$(CC) $(CC_FLAGS) -o $@ $^

$(LS): $(LS_SRC_FILES)
	@echo "[ PROGRAMS ][ LS ] (CC) $@ . . ."
	@$(CC) $(CC_FLAGS) -o $@ $^

$(TRUNCATE): $(TRUNCATE_SRC_FILES)
	@echo "[ PROGRAMS ][ TRUNCATE ] (CC) $@ . . . "
	@$(CC) $(CC_FLAGS) -o $@ $^


dirs:
	@mkdir -p $(BIN_DIR)

# . RULES
.PHONY: dirs