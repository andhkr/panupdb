#include "include/command_traffic_police.hpp"

int main(int argc, char** argv) {
    /*load databases available*/
    databases_loading();
    /* connect to default database*/
    std::string cmd = "\\c default_db";
    cli_command_executor(cmd);
    cmd.clear();
    while (run) {
        std::cout << "induman@panupdb$ ";
        read_and_execute_command();
    }
    // int* leak = new int[10];
    // leak[0] = 123;  // Use it to prevent optimization

    return 0;
}