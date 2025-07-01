#include "include/command_traffic_police.hpp"

int main(int argc, char** argv) {
    /*load databases available*/
    databases_loading();

    while (run) {
        std::cout << "induman@panupdb$ ";
        read_and_execute_command();
    }
    
    return 0;
}