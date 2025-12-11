CC = gcc
CP = g++

POSLED = Posled 
PTHREADS = PThreads
CPPTHREAD = cppthread

.SILENT: $(CPPTHREAD)

all: $(POSLED) $(PTHREADS) $(CPPTHREAD)

$(POSLED):Posled.c 
	@ $(CC) Posled.c -o $(POSLED)

$(PTHREADS):PThreads.c 
	@ $(CC) PThreads.c -o $(PTHREADS)

$(CPPPTHREAD):cppthread.cpp 
	@ $(CP) cppthread.cpp -o $(CPPTHREAD)

clean:
	@ rm -f $(POSLED) $(PTHREADS) $(CPPTHREAD)

.PHONY: all clean