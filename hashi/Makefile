CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g
DEPFLAGS := -MMD -MP

TARGET := app
OBJ_DIR := obj

SOURCES := main.cpp \
           engine/GraphBuilder.cpp \
           engine/GameUtils.cpp \
           engine/Moves.cpp \
           engine/Validators.cpp \
           levels/LevelManager.cpp \
           render/ConsoleRender.cpp \
           ui/ConsoleUI.cpp

OBJECTS := $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)
DEPS := $(OBJECTS:.o=.d)

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile with dependency generation
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

# Include header dependencies
-include $(DEPS)

# Run
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -DDEBUG
debug: clean all

# Clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean run debug
