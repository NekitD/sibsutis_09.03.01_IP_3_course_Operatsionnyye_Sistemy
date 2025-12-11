CC = gcc
CFLAGS = -Wall -Wextra -g -fPIC
TARGET = liblist.so
MAIN = main
OBJ = list.o
MAIN_OBJ = main.o

all: $(TARGET) $(MAIN)

$(TARGET): $(OBJ)
	@ $(CC) -shared -o $@ $^

$(OBJ): list.c list.h
	@ $(CC) $(CFLAGS) -c list.c -o $@

$(MAIN_OBJ): main.c list.h
	@ $(CC) $(CFLAGS) -c main.c -o $@

$(MAIN): $(MAIN_OBJ) $(TARGET)
	@ $(CC) $(CFLAGS) -o $@ $(MAIN_OBJ) -L. -llist -Wl,-rpath,.

clean:
	@ rm -f *.o $(TARGET) $(MAIN)

debug: $(MAIN)
	@ gdb ./$(MAIN)

objects: $(OBJ) $(MAIN_OBJ)

.PHONY: all clean debug objects
