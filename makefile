# Sanitizer flags
# SANITIZER_FLAGS = -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer
# LDFLAGS = $(SANITIZER_FLAGS)
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I. -I$(BUILD_DIR) -g
CXXFLAGS += $(SANITIZER_FLAGS)
LEX = flex
YACC = bison
YFLAGS = -d -v -Wcounterexamples

# Target executable
TARGET = sql_parser

# Source directories
SRC_DIR = src
INC_DIR = include

# Output directories
BUILD_DIR = build
BIN_DIR = bin
DATABASE = databases

# Output paths
PARSER_CPP = $(BUILD_DIR)/sql.tab.cpp
PARSER_HPP = $(BUILD_DIR)/sql.tab.hpp
LEXER_CPP = $(BUILD_DIR)/lex.yy.cpp

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) 
SOURCES += $(wildcard $(SRC_DIR)/backened/*.cpp)
GENERATED_SOURCES = $(PARSER_CPP) $(LEXER_CPP)

# Object files - create properly substituted object file names
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(filter $(SRC_DIR)/%.cpp,$(SOURCES)))
OBJECTS += $(patsubst $(SRC_DIR)/backened/%.cpp,$(BUILD_DIR)/backened/%.o,$(filter $(SRC_DIR)/backened/%.cpp,$(SOURCES)))
GENERATED_OBJECTS = $(GENERATED_SOURCES:$(BUILD_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Ensure build and bin directories exist
$(shell mkdir -p $(BUILD_DIR))
$(shell mkdir -p $(BUILD_DIR)/backened)
$(shell mkdir -p $(BIN_DIR))
$(shell mkdir -p $(DATABASE))

# Default target
all: $(BIN_DIR)/$(TARGET)

# Link object files to create executable
$(BIN_DIR)/$(TARGET): $(OBJECTS) $(GENERATED_OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^



$(BUILD_DIR)/command_traffic_police.o: $(SRC_DIR)/command_traffic_police.cpp $(PARSER_HPP)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile source files from src directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile source files from src/backened directory
$(BUILD_DIR)/backened/%.o: $(SRC_DIR)/backened/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile generated parser
$(BUILD_DIR)/sql.tab.o: $(PARSER_CPP)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile generated lexer
$(BUILD_DIR)/lex.yy.o: $(LEXER_CPP)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Generate parser from Bison grammar
$(PARSER_CPP) $(PARSER_HPP): $(SRC_DIR)/sql.y
	$(YACC) $(YFLAGS) -o $(PARSER_CPP) $<

# Generate lexer from Flex specification
$(LEXER_CPP): $(SRC_DIR)/sql.l $(PARSER_HPP)
	$(LEX) --outfile=$@ $<

# Clean up generated files
clean:
	@read -p "Are you sure you want to clean all build files? (y/n): " ans; \
	if [ "$$ans" = "y" ] || [ "$$ans" = "Y" ]; then \
		echo "Cleaning..."; \
		rm -rf $(BUILD_DIR)/* $(BIN_DIR)/* \
	else \
		echo "Clean aborted."; \
	fi

# Rebuild everything
rebuild: clean all

.PHONY: all clean rebuild