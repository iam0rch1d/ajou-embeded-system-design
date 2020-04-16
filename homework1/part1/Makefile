# Macros
CC=gcc
CFLAGS=-O2 -g
OBJS=part1.o part1_funcs.o
TARGET=part1.out

# Make
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
