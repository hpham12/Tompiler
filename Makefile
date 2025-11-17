# Compiler and flags
CXX      := g++
CXXFLAGS := -Wall -Wextra -MMD -MP -arch x86_64 -std=c++20

# Build type: debug (default) or release
BUILD_TYPE ?= debug

ifeq ($(BUILD_TYPE),debug)
  CXXFLAGS += -O0 -g
  TARGET_SUFFIX := 
else
  CXXFLAGS += -O2
  TARGET_SUFFIX := .release
endif

# Folders
SRC_DIR := src
OBJ_DIR := build/$(BUILD_TYPE)

# Find all source files recursively
SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')

# Map src/.../file.cpp -> build/debug/.../file.o
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
TARGET := tpl$(TARGET_SUFFIX)

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Compile rule (auto-creates nested build/ dirs)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -rf build $(TARGET) tpl.release

# Phony targets
.PHONY: all clean debug release

# Convenience targets
debug:
	$(MAKE) BUILD_TYPE=debug

release:
	$(MAKE) BUILD_TYPE=release

# Include auto-generated dependency files
-include $(DEPS)
