CXX        := g++
CXXFLAGS   := -std=c++17 -O2 -Isrc -Wall -Wextra -Werror
LDFLAGS    := -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR    := src
BUILD_DIR  := build
TARGET     := snake_game
TARGET_BIN := $(BUILD_DIR)/$(TARGET)

SRCS       := $(wildcard $(SRC_DIR)/*.cpp)
OBJS       := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all clean

all: $(BUILD_DIR) $(TARGET_BIN)

$(TARGET_BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)
