CC = gcc
CFLAGS = -Wall -Wextra -g -rdynamic
LOADER = dynamic_loader
LIB_SOURCE_DIR = ../Lab5
LIBRARY = liblist.so

.PHONY: all clean monitor

all: $(LOADER) $(LIBRARY)

$(LOADER): dynamic_loader.c
	$(CC) $(CFLAGS) -o $@ $< -ldl

$(LIBRARY): $(LIB_SOURCE_DIR)/list.c $(LIB_SOURCE_DIR)/list.h
	$(CC) -fPIC -shared -o $@ $(LIB_SOURCE_DIR)/list.c

clean:
	rm -f $(LOADER) $(LIBRARY)

monitor: $(LOADER) $(LIBRARY)
	@echo "Starting real-time monitoring..."
	./$(LOADER)

.PHONY: all clean monitor
