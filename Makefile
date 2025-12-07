# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Ilib

# Output executable name
TARGET = merxq

# Source files
SOURCES = src/main.cpp \
          src/utils.cpp \
          src/user.cpp \
          src/customer.cpp \
          src/admin.cpp \
          src/product.cpp \
          src/cart.cpp \
          src/order.cpp \
          src/filemanager.cpp \
          src/application.cpp

# Build the project
all: $(TARGET)
	@echo "Build successful! Run with: ./$(TARGET)"

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Run the application
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)
	@echo "Cleaned!"
