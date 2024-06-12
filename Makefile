CC = gcc

CFLAGS = -pthread

SRCS = main.c threaded.c sequential.c

HEADERS = threaded.h sequential.h

TARGET = main

matrix_size ?= 24
num_threads ?= 4

DEFINES = -DMATRIX_SIZE=$(matrix_size) -DNUM_THREADS=$(num_threads)

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS) FORCE
	$(CC) $(CFLAGS) $(DEFINES) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean

FORCE:
