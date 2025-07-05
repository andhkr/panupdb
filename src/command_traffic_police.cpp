#include "include/command_traffic_police.hpp"
/*--currently connected databse*/
std::string current_database;
/*--created databases*/
std::unordered_set<std::string> databases_created;

bool connected_to_a_database=false;
/*point by which database will be accessed*/
catalog_manager* catlg_man = nullptr;
/*this stores the path of all  files of cuurent database*/
std::unordered_map<uint,std::string> file_id_filename_lookup;
/*current database path in filesystem*/
std::string database_path {};
/*panupdb root directory*/
std::string database_root {"databases"};
bool run{true};

/*when database start it will load all created databases in unordered_set*/
void databases_loading(){
    DIR* dirp = opendir(database_root.c_str());

    if(!dirp){
        perror("opendir failed");

        exit(EXIT_FAILURE);
    }

    struct dirent* entry;

    while((entry = readdir(dirp)) != nullptr){
        if(entry->d_type == DT_DIR){
            databases_created.insert(std::string(entry->d_name));
        }
    }
}

/*
if cmd start with / that means it have nothing to do with parsing and query planning
otherwise treated as sql query
*/
std::string trim(std::string subcmd){
    auto start = std::find_if_not(subcmd.begin(),subcmd.end(),::isspace);
    auto end = std::find_if_not(subcmd.rbegin(),subcmd.rend(),::isspace).base();
    /*--slicing will work with forward iterator so .base() will give cooresponding forward iterator 
    pointing just after the element pointed by reverse iterator*/
    if(start>=end) return "";
    return std::string(start,end);
}

void tables_in_database(){
    for(auto& tables : catlg_man->catalog_file_list){
        std::cout<<tables.first<<std::endl;
    }
}

void print_help(){
    std::cout<<"help\n"<<
    "\\c {database name} : to connect to existing database\n" <<
    "\\d {table_name}    : to get the details of table in connected databse\n"<<
    "\\dt                : to get the list of tables in connected database\n"<<
    "\\l                 : to get the list of created databases\n"<<
    "\\q                 : to quit from panupdb"<<std::endl;
}

void cli_command_executor(std::string& cmd){
    cmd = trim(cmd);
    std::string prefix = cmd.substr(0,2);
    if(prefix == "\\c"){
        /*--now take database name -> trim the cmmand from front and back to avoid spaces*/
        std::string database_name = trim(cmd.substr(2));
        if(database_name.size() == 0){
            std::cerr<<"please give valid database name"<<std::endl;
            return;
        }
        /*--first check whether this database exist or not*/
        if(databases_created.find(database_name) == databases_created.end()){
            std::cerr<<"given database does not exist"<<std::endl;
            return;
        }

        /*--now if already there is connection to a database that connection will be shutdown 
        and new connection will be establish with other database , if requested database is 
        current database then nothing will be performed*/

        if(connected_to_a_database && current_database == database_name) return;
        if(connected_to_a_database){
            /*shutdown the existing database and establish new connection*/
            delete catlg_man; /* destructor will do furthur shutdown */
            catlg_man = nullptr;
            
        }

        current_database = database_name;
        database_path = database_root + "/" + database_name + "/";
        catlg_man = new catalog_manager();
        connected_to_a_database = true;
        std::cout<<"connected to database "<<database_name<<std::endl;
    }else if (prefix == "\\d"){
        /*--first check whether connected to a database or not*/
        if(!connected_to_a_database){
            std::cerr<<"please connect to a valid database"<<std::endl;
            return;
        }

        std::string table_name = trim(cmd.substr(2));
        if(table_name.size() == 0){
            /*action similar to '\dt' that is show all tables*/
            tables_in_database();
        }else{
            /*check whether this table exist or not*/
            if(catlg_man->catalog_file_list.find(table_name) == catlg_man->catalog_file_list.end()){
                std::cerr<<"please give the existing table"<<std::endl;
                return;
            }
            /*information about table*/
            catlg_man->catalog_file_list[table_name]->print();
        }
    }else if(cmd == "\\dt"){
        /*--first check whether connected to a database or not*/
        if(!connected_to_a_database){
            std::cerr<<"please connect to a valid database"<<std::endl;
            return;
        }
        /*--give tables in database*/
        tables_in_database();
    }else if(cmd == "\\l"){
        /*list all database present*/
        for(auto& database:databases_created){
            std::cout<<database<<std::endl;
        }
    }else if(cmd == "\\q"){
        /*quit from panupdb*/
        /*--before removing shutdown the current database connection*/
        delete catlg_man;
        catlg_man = nullptr;
        run = false;
    }else if(cmd == "\\?"){
        print_help();
    }
    else{
        std::cerr<<"Try \\? for help"<<std::endl;
    }
}


void sql_query_executor(std::string& cmd){
    yy_scan_string(cmd.c_str());   // Let Flex scan the input string
    yyparse();                       // Parse it
    yylex_destroy();
}

void get_database_cmd(std::string& cmd){
    char c;
    while (std::cin.get(c)) { 
        if (c == '\n') break;
        cmd.push_back(c);
    }
}

void get_sql_query(std::string& query) {
    char c;
    while (std::cin.get(c)) { 
        if(c == '\n') continue;
        if (c == ';'){
            query.push_back(c);
            break;
        }
        query.push_back(c);
    }
    std::cin.ignore();
}

void read_and_execute_command(){
    std::string cmds{};
    char c;
    std::cin.get(c);
    cmds.push_back(c);
    if(c == '\\'){
        get_database_cmd(cmds);
        cli_command_executor(cmds);
    }else{
        get_sql_query(cmds);
        sql_query_executor(cmds);
    }
}

