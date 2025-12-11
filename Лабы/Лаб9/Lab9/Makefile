CC = gcc

L_SOURCE = SpinLessTest.c 
L_TARGET = SpinLessTest

R_SOURCE = SpinTest.c 
R_TARGET = SpinTest


all: $(L_TARGET) $(R_TARGET)

$(L_TARGET): $(L_SOURCE)
	@ $(CC) $(L_SOURCE) -o $(L_TARGET)

$(R_TARGET): $(R_SOURCE)
	@ $(CC) $(R_SOURCE) -o $(R_TARGET)

clean:
	@ rm $(L_TARGET) $(R_TARGET)

.PHONY: all clean