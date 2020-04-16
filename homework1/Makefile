# Macros
CC=gcc
CFLAGS=-O2 -g
SUBDIRS=part1 part2 part2/part3
OBJS=homework1.o homework1_funcs.o
TARGET=homework1.out
CLEANTARGET=fileSumProduct.dat
	    part1/part1.o part1/part1_funcs.o part1/part1.out \
	    part2/part2.o part2/part2_funcs.o part2/part2.out \
	    part2/part3/part3.o part2/part3/part3_funcs.o part2/part3/part3.out
SRCS=$(OBJS:.o=.c)

# Suffix rules
.SUFFIXES: .c .o

# Make
all: subdirs $(TARGET)

subdirs:
	@for dir in $(SUBDIRS); do \
	    $(MAKE) -C $$dir all; \
	    if [$$? != 0]; then exit 1; fi; \
	done

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET) $(CLEANTARGET)
