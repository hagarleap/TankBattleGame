# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++20

# Source files
SRCS = main.cpp \
       GameManager.cpp \
       InputParser.cpp \
       Board.cpp \
       Tank.cpp \
       Shell.cpp \
       Position.cpp \
       Direction.cpp \
       Tile.cpp \
       TestAlgorithm.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output executable
TARGET = TankGame

# Default build rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)
