#include <iostream>
#include <string>
#include <sstream>
#include "include/ast.hpp"
#include "include/datatypes.hpp"
#include "build/sql.tab.hpp"  // Bison-generated header

// Flex function declarations
extern void yy_scan_string(const char* str);
extern void yylex_destroy();

// If using Bison C++ API with namespace
// using namespace SQL; // Uncomment if you used %define api.namespace {SQL} in sql.y

int main(int argc, char** argv) {
    while (true) {
        std::cout << "induman@panupdb$ ";
        std::string query;
        std::getline(std::cin, query);

        if (query == "\\exit") {
            break;
        }

        // Pass the string to lexer/parser
        yy_scan_string(query.c_str());   // Let Flex scan the input string
        yyparse();                       // Parse it
        yylex_destroy();                 // Reset scanner
    }
    
    return 0;
}