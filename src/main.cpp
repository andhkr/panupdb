#include <iostream>
#include <string>
#include <sstream>
#include "include/ast.hpp"
#include "include/datatypes.hpp"
#include "build/sql.tab.hpp"  // Bison-generated header
#include "include/backened/catalog_manager.hpp"
#include "include/backened/table.hpp"
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <algorithm>


// Flex function declarations
extern void yy_scan_string(const char* str);
extern void yylex_destroy();

std::unordered_map<uint,std::string> file_id_filename_lookup;
catalog_manager* catlg_man = nullptr;
std::string database_path {};

std::vector<std::string> databases;
bool connected_to_a_database=false;

std::string trim(std::string subcmd){
    auto start = std::find_if_not(subcmd.begin(),subcmd.end(),::isspace);
    auto end = std::find_if_not(subcmd.rbegin(),subcmd.rend(),::isspace).base();
    if(start>=end) return "";
    return std::string(start,end);
 }

enum return_type{
    exit_while,
    query_execute,
    next_cmd
};

return_type cl_cmd_executor(std::string& cmd){
    std::string prefix = cmd.substr(0,2);
    if(prefix == "\\c") {
        /*verify that that exists other wise give create database cmd*/
        /*
        std::string database_name = trim(cmd.substr(2));
        auto it = std::find(databases.begin(),databases.end(),database_name);
        if(it == databases.end()){
            std::cout<<"database : "<<database_name<<" does not exist"<<std::endl;
            return false;
        }
        database_path.clear();
        database_path = "databases";
        */

        database_path = database_path + "/" + "anup"+"/";
        catlg_man = new catalog_manager();
        catlg_man->file_id = 0;
        connected_to_a_database = true;
    }else if (prefix == "\\d"){
        std::string table_name = trim(cmd.substr(2));
        if(table_name.size()==0 && connected_to_a_database){
            for(auto& tables : catlg_man->catalog_file_list){
                std::cout<<tables.first<<std::endl;
            }
        }else if(!connected_to_a_database){
            std::cout<<"please connect to a databse"<<std::endl;
        }else{
            catlg_man->catalog_file_list[table_name]->print();
        }
        
    }else if (prefix == "\\l"){
        for(auto& database_name:databases){
            std::cout<<database_name<<std::endl;
        }
    }
    else if(trim(cmd.substr(1)) == "exit"){
        catlg_man->write_file_lookup();
        catlg_man->buffer_pool_manager.flush_all_pages();
        return exit_while;
    }else return query_execute;
    return next_cmd;
}

void databases_loading(){
    DIR* dirp = opendir(database_path.c_str());

    if(!dirp){
        perror("opendir failed");

        exit(EXIT_FAILURE);
    }

    struct dirent* entry;

    while((entry = readdir(dirp)) != nullptr){
        if(entry->d_type == DT_DIR){
            databases.push_back(std::string(entry->d_name));
        }
    }
}

int main(int argc, char** argv) {
    database_path = "databases";
    /*load databases*/
    databases_loading();

    bool run = true;
    while (run) {
        std::cout << "induman@panupdb$ ";
        std::string query;
        std::getline(std::cin, query);

        switch(cl_cmd_executor(query)){
            case query_execute:{
                // if sql query Pass the string to lexer/parser
                yy_scan_string(query.c_str());   // Let Flex scan the input string
                yyparse();                       // Parse it
                yylex_destroy();                 // Reset scanner
                break;
            }
            case exit_while:{
                run = false;
                break;
            }
            default:{
                break;
            }
        }
    }
    
    return 0;
}