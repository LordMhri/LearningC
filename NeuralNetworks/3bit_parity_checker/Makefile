#compiler and compiler flags
CC = gcc
CFLAGS = -Wall -g -pedantic 

#executable name
TARGET = checker.bin

# source file
SRC = main.c neural.c 

# Default target
all: $(TARGET)


#compiler src to an executable named $(TARGET) with the given flags 
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -lm

# remove generated file
clean:
	rm -f $(TARGET)   # This line also needs to have a TAB
