 
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = elf_analyz
LIBRARY = ../Lab5/liblist.so

.PHONY: all clean test

all: $(TARGET)

$(TARGET): elf_analyz.c
	$(CC) $(CFLAGS) -o $@ $<


test: $(TARGET) $(LIBRARY)
	@echo "=== Testing on library ==="
	./$(TARGET) $(LIBRARY)

clean:
	rm -f $(TARGET) $(LIBRARY) *.o
