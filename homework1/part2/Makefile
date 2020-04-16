# Macros
CC=gcc
CFLAGS=-O2 -g
OBJS=part2.o part2_funcs.o
TARGET=part2.out
CLEANTARGET=fileSumProduct.dat

# Make
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET) $(CLEANTARGET)
