CXX = g++
CXXFLAGS = -std=c++17 -Wall -I. -I$(BUILD_DIR)
LEX = flex
YACC = bison
YFLAGS = -d -v

# Target executable
TARGET = sql_parser

# Source directories
SRC_DIR = src
INC_DIR = include

# Output directories
BUILD_DIR = build
BIN_DIR = bin

# Output paths
PARSER_CPP = $(BUILD_DIR)/sql.tab.cpp
PARSER_HPP = $(BUILD_DIR)/sql.tab.hpp
LEXER_CPP = $(BUILD_DIR)/lex.yy.cpp

# Source files
SOURCES = $(SRC_DIR)/main.cpp
GENERATED_SOURCES = $(PARSER_CPP) $(LEXER_CPP)

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
GENERATED_OBJECTS = $(GENERATED_SOURCES:$(BUILD_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Ensure build and bin directories exist
$(shell mkdir -p $(BUILD_DIR))
$(shell mkdir -p $(BIN_DIR))

# Default target
all: $(BIN_DIR)/$(TARGET)

# Link object files to create executable
$(BIN_DIR)/$(TARGET): $(OBJECTS) $(GENERATED_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile main.cpp (depends on generated parser header)
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(PARSER_HPP)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile other source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
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
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/* 

# Rebuild everything
rebuild: clean all

.PHONY: all clean rebuild