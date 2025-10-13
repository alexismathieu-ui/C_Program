# Variables
CC = gcc
CFLAGS = -Wall -I.     # -I. tells the compiler to look for headers in the current directory
LDFLAGS = -L. -lsquares -lcsfml-graphics -lcsfml-window
TARGET = main
SRC = main.c

# Default rule to compile the program
all: $(TARGET)

# Rule to build the target
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

# Clean rule to remove the generated files
clean:
	rm -f $(TARGET)