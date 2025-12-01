# ==========================================
# Makefile for Antenna Placement Solution
# ==========================================

# Compiler and Flags
CC = gcc
# -Wall: Enable all warnings
# -Wextra: Enable extra warnings
# -g: Add debug symbols (useful for gdb/valgrind)
# -std=c99: Use C99 standard
CFLAGS = -Wall -Wextra -g -std=c99

# Target Executable Name
TARGET = antenna_solver

# Source Files
SRC = main.c

# ==========================================
# Rules
# ==========================================

# Default target: builds the executable
all: $(TARGET)

# Rule to link the object file to create the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up build artifacts (useful before committing to Git)
clean:
	rm -f $(TARGET)

# Phony targets verify that 'all' and 'clean' are not files
.PHONY: all clean
