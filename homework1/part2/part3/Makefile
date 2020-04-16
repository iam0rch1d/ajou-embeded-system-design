# Macros
CC=gcc
CFLAGS=-O2 -g
OBJS=part3.o part3_funcs.o
TARGET=part3.out

# Make
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
