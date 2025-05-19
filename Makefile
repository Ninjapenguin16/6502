# Compilers and flags
CC := gcc
CXX := g++
CFLAGS := -Wall -Wextra -std=c11 -O2
CXXFLAGS := -Wall -Wextra -std=c++11 -O2

# Directories
SRC_DIR := src
BUILD_DIR := build

# Source and object files
C_SRCS := $(wildcard $(SRC_DIR)/*.c)
CPP_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
C_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SRCS))
CPP_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_SRCS))
OBJS := $(C_OBJS) $(CPP_OBJS)

# Output binary
TARGET := $(BUILD_DIR)/6502

.PHONY: all clean

all: $(TARGET)

# Link final binary using g++ to include C++ standard library
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

# Compile .c files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile .cpp files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm $(BUILD_DIR)/*