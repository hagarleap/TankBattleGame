# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++20

# Auto-detect all .cpp files
SRCS := $(wildcard *.cpp)

# Output executable
TARGET = TankGame

# Default build rule
all: $(TARGET)

# Build the executable directly from .cpp files
$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean rule
clean:
	rm -f $(TARGET)