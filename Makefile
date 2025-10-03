# Compiler and flags
CXX      := g++
CXXFLAGS := -Wall -Wextra -O2 -MMD -MP -arch x86_64 -std=c++20

# Folders
SRC_DIR := src
OBJ_DIR := build

# Find all source files recursively
SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')

# Map src/.../file.cpp -> build/.../file.o
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
TARGET := tpl

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ -arch x86_64

# Compile rule (auto-creates nested build/ dirs)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Include auto-generated dependency files
-include $(DEPS)
