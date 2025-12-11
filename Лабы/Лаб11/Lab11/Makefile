CC = gcc


END_SOURCE = end_buffer.c 
END_TARGET = end_buffer

CYC_SOURCE = cycle_buffer.c 
CYC_TARGET = cycle_buffer

all: $(END_TARGET) $(CYC_TARGET)

$(END_TARGET): $(END_SOURCE)
	@ $(CC) $(END_SOURCE) -o $@

$(CYC_TARGET): $(CYC_SOURCE)
	@ $(CC) $(CYC_SOURCE) -o $@

clean:
	@ rm $(END_TARGET) $(CYC_TARGET)

.PHONY: all clean