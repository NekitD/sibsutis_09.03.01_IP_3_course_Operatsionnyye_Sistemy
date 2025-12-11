CC = gcc
CPP = g++
CFLAGS = -Wall -pthread

P8_SOURCE = Peterson8.c 
P8_TARGET = Peterson8

P9_SOURCE = Peterson9.c 
P9_TARGET = Peterson9

AP_SOURCE = atomPeterson9.cpp 
AP_TARGET = atomPeterson9

all: $(P8_TARGET) $(P9_TARGET) $(AP_TARGET)

$(P8_TARGET): $(P8_SOURCE)
	@ $(CC) $(P8_SOURCE) -o $(P8_TARGET)

$(P9_TARGET): $(P9_SOURCE)
	@ $(CC) $(CFLAGS) -o $@ $<

$(AP_TARGET): $(AP_SOURCE)
	@ $(CPP) $(AP_SOURCE) -o $(AP_TARGET)

clean:
	@ rm $(P8_TARGET) $(P9_TARGET) $(AP_TARGET)

.PHONY: all clean