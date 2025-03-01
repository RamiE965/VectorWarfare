CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRC_DIR = src
BIN_DIR = bin
IMGUI_DIR = $(SRC_DIR)/imgui

INCLUDES = -I$(SRC_DIR) -I$(IMGUI_DIR)

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lGL

IMGUI_SOURCES = $(IMGUI_DIR)/imgui.cpp \
                $(IMGUI_DIR)/imgui_draw.cpp \
                $(IMGUI_DIR)/imgui_tables.cpp \
                $(IMGUI_DIR)/imgui_widgets.cpp \
                $(IMGUI_DIR)/imgui-SFML.cpp

SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/Game.cpp \
          $(IMGUI_SOURCES)

OBJECTS = $(SOURCES:%.cpp=$(BIN_DIR)/%.o)

EXECUTABLE = $(BIN_DIR)/VectorWarfare

all: directories $(EXECUTABLE)

directories:
	mkdir -p $(BIN_DIR)
	mkdir -p $(BIN_DIR)/$(SRC_DIR)
	mkdir -p $(BIN_DIR)/$(IMGUI_DIR)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(BIN_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)

run: all
	$(EXECUTABLE)

.PHONY: all directories clean run