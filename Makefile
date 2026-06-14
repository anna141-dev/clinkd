CC      := gcc
CFLAGS  := -Wall -Wextra -Iinclude
AR      := ar
ARFLAGS := rcs

OUT_DIR := output

LIB     := $(OUT_DIR)/libclinkd.a
TARGET  := $(OUT_DIR)/test_runner

SRC_LIB  := $(wildcard src/*.c)
OBJ_LIB  := $(SRC_LIB:src/%.c=$(OUT_DIR)/%.o)

SRC_TEST := $(wildcard tests/*.c)
OBJ_TEST := $(SRC_TEST:tests/%.c=$(OUT_DIR)/tests/%.o)

.PHONY: all lib run clean

all: $(LIB) $(TARGET)

lib: $(LIB)

# rule to create the test executable
$(TARGET): $(OBJ_TEST) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(OBJ_TEST) -L$(OUT_DIR) -lclinkd

# rule to create the static library
$(LIB): $(OBJ_LIB)
	$(AR) $(ARFLAGS) $@ $^

# compilation of librart objects (/src/*.c -> /src/*.o)
$(OUT_DIR)/%.o: src/%.c
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# compilation of test objects (/tests/*.c -> /tests/*.o)
$(OUT_DIR)/tests/%.o: tests/%.c
	@mkdir -p $(OUT_DIR)/tests
	$(CC) $(CFLAGS) -c $< -o $@

# run the tests
run: all
	./$(TARGET)

# cleans everything on /output/
clean:
	rm -rf $(OUT_DIR)
