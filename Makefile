# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -O2

# Directories
SRC_DIR := src
BUILD_DIR := build

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Output binary
TARGET := $(BUILD_DIR)/6502

.PHONY: all clean

all: $(TARGET)

# Link the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c to .o into the build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm $(BUILD_DIR)\*
