CC=gcc

CFLAGS=-Wall -g -std=c99

SRCDIR=./

SRC=$(shell find $(SRCDIR) -name '*.c')

TARGET= ./bin/test

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lpthread

clean:
	rm -rf $(TARGET)