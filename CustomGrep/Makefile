#compiler and compiler flags
CC = gcc
CFLAGS = -Wall -g

#executable name
TARGET = search.bin

# source file
SRC = customGrep.c

# Default target
all: $(TARGET)


#compiler src to an executable named $(TARGET) with the given flags 
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# remove generated file
clean:
	rm -f $(TARGET)   # This line also needs to have a TAB
