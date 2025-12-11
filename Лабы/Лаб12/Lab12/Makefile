CC = gcc


BASE_SOURCE = src/lab13b.c 
BASE_TARGET = obj/lab13b

FILE_WRITER_SOURCE = src/lab13c-1.c
FILE_WRITER_TARGET = obj/lab13c-1

FILE_READER_SOURCE = src/lab13c-2.c
FILE_READER_TARGET = obj/lab13c-2

POSIX_WRITER_SOURCE = src/lab13d-1.c
POSIX_WRITER_TARGET = obj/lab13d-1

POSIX_READER_SOURCE = src/lab13d-2.c
POSIX_READER_TARGET = obj/lab13d-2

all: $(BASE_TARGET) $(FILE_WRITER_TARGET) $(FILE_READER_TARGET) $(POSIX_WRITER_TARGET) $(POSIX_READER_TARGET)

$(BASE_TARGET): $(BASE_SOURCE)
	@ $(CC) $(BASE_SOURCE) -o $@

$(FILE_WRITER_TARGET): $(FILE_WRITER_SOURCE)
	@ $(CC) $(FILE_WRITER_SOURCE) -o $@

$(FILE_READER_TARGET): $(FILE_READER_SOURCE)
	@ $(CC) $(FILE_READER_SOURCE) -o $@

$(POSIX_WRITER_TARGET): $(POSIX_WRITER_SOURCE)
	@ $(CC) $(POSIX_WRITER_SOURCE) -lrt -o $@

$(POSIX_READER_TARGET): $(POSIX_READER_SOURCE)
	@ $(CC) $(POSIX_READER_SOURCE) -lrt -o $@

clean:
	@ rm obj/*


run-file-writer:
	./obj/lab13c-1

run-file-reader:
	./obj/lab13c-2

run-posix-writer:
	./obj/lab13d-1

run-posix-reader:
	./obj/lab13d-2



.PHONY: all clean run-file-reader run-file-writer run-posix-reader run-posix-writer