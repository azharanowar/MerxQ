# MerxQ Makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Ilib

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Target executable
TARGET = merxq

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✓ Build successful! Run with: ./$(TARGET)"

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "✓ Cleaned build artifacts"

# Rebuild
rebuild: clean all

# Help
help:
	@echo "MerxQ Build System"
	@echo "make       - Build the project"
	@echo "make run   - Build and run"
	@echo "make clean - Remove build artifacts"

.PHONY: all run clean rebuild help
