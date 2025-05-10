CC = gcc
CFLAGS = -Wall -Iinclude
OBJ = src/feistel.o main.o
TARGET = feistel

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

src/feistel.o: src/feistel.c include/feistel.h
	$(CC) $(CFLAGS) -c src/feistel.c -o src/feistel.o

clean:
	rm -f $(OBJ) $(TARGET)
