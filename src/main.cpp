#include <iostream>
#include <string>

int main(int argc,char** argv){
    while(true){
        std::cout<<"induman@panupdb$";
        std::string query;
        std::getline(std::cin,query);
        if(query == "\\exit"){
            break;
        }
        
        std::cout<<"the query taken:"<<std::endl;
        std::cout<<query<<std::endl;
    }
}