#ifndef COMMAND_TRAFFIC_POLICE_HPP
#define COMMAND_TRAFFIC_POLICE_HPP

#include <iostream>
#include <string>
#include "include/ast.hpp"
#include "build/sql.tab.hpp"  // Bison-generated header
#include <algorithm>
#include <unordered_map>
#include "backened/catalog_manager.hpp"
#include <unordered_set>
#include <sys/types.h>
#include <dirent.h>

extern void yy_scan_string(const char* str);
extern void yylex_destroy();
/*--currently connected databse*/
extern std::string current_database;
/*--created databases*/
extern std::unordered_set<std::string> databases_created;

extern bool connected_to_a_database;
/*point by which database will be accessed*/
extern catalog_manager* catlg_man;
/*this stores the path of all  files of cuurent database*/
extern std::unordered_map<uint,std::string> file_id_filename_lookup;
/*current database path in filesystem*/
extern std::string database_path;
/*panupdb root directory*/
extern std::string database_root;

extern bool run;

/*when database start it will load all created databases in unordered_set*/
void databases_loading();

/*
if cmd start with / that means it have nothing to do with parsing and query planning
otherwise treated as sql query
*/
std::string trim(std::string subcmd);

void tables_in_database();

void print_help();

void cli_command_executor(std::string& cmd);

void sql_query_executor(std::string& cmd);

void get_database_cmd(std::string& cmd);

void get_sql_query(std::string& query);

void read_and_execute_command();

#endif