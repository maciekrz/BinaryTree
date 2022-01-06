CC = g++

CFLAGS = -g -Wall

all: binarytree

binarytree:
	$(CC) $(CFLAGS) -O2 -o ./binarytree ./src/*.cpp

debug:
	$(CC) $(CFLAGS) -g -O0 -o ./binarytree ./src/*.cpp
	gdb binarytree

clean:
	rm binarytree
