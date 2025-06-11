#ifndef FREE_SPACE_MANAGER
#define FREE_SPACE_MANAGER

#include "page.hpp"
#include <set>
#include <unordered_map>

struct per_page_free_space{
    size_t free_space=0;
    uint page_id=0;

    per_page_free_space()=default;
    per_page_free_space(size_t space,uint id);

    bool operator<(const per_page_free_space& o) const noexcept;

    size_t get_object_total_size()const;

    size_t serialise(char* buffer)const;

    size_t deserialise(const char* buffer);
};


struct free_space_manager {
    /*per file free_space_set*/
    std::set<per_page_free_space> PPFSS;
    /*per file free space set : unordered_map (file_id,free_space_set)*/
    std::unordered_map<uint,std::set<per_page_free_space>> PF_FSS;
    /*to locate a page in container in O(1)*/
    std::unordered_map<uint,std::unordered_map<uint,std::set<per_page_free_space>::iterator>> page_location;
    
    free_space_manager()=default;

    /*initialisation of PPFSS and PF_FSS is done by Catalog Manager*/

    void update_available_space(uint file_id,uint page_id,size_t available_space);

    void add_page_space(uint file_id,uint page_id,size_t available_space);

    int get_page_with_available_space(size_t required_space,uint file_id) ;

};

#endif