# Define the compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Target executable
TARGET = p1

# Source files
SRCS = main.c parse.c utility.c

# Header files
HEADERS = parse.h utility.h

# Object files (generated from source files)
OBJS = $(SRCS:.c=.o)

# Default rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile .c files into .o files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the target executable
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
