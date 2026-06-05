CC      := gcc
CFLAGS  := -Wall -Wextra -Iinclude
AR      := ar
ARFLAGS := rcs

TARGET  := output/clinkd
LIB     := output/libclinkd.a

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=output/%.o)

LIB_OBJS := $(filter-out output/main.o, $(OBJS))

.PHONY: all lib run clean

all: $(TARGET)

lib: $(LIB)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(LIB): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

output/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(LIB)
