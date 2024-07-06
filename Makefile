# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra

# SFML directory and libraries
SFML_DIR := ./sfml
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

# Include and library paths
INC := -I$(SFML_DIR)/include
LIB := -L$(SFML_DIR)/lib

# Source files
SRCS := $(wildcard *.cpp)

# Object files
OBJS := $(SRCS:.cpp=.o)

# Executable name
EXEC := graphit

# Build target
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIB) $(OBJS) -o $(EXEC) $(SFML_LIBS)

# Object files compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(EXEC)
