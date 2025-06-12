#include "include/backened/free_space_manager.hpp"

per_page_free_space::per_page_free_space(size_t space,uint id):free_space(space),page_id(id){}

bool per_page_free_space::operator<(const per_page_free_space& o) const noexcept {
    return std::tie(free_space, page_id)
         < std::tie(o.free_space, o.page_id);
}


size_t per_page_free_space::get_object_total_size() const{
    return sizeof(free_space) + sizeof(page_id);
}

size_t per_page_free_space::serialise(char* buffer)const{
    size_t offset = 0;

    auto write = [&](const void* src,size_t size){
        memcpy(buffer+offset,src,size);
        offset+= size;
    };

    write(&free_space,sizeof(free_space));
    write(&page_id,sizeof(page_id));

    return offset;
}

size_t per_page_free_space::deserialise(const char* buffer){
    size_t offset = 0;

    auto read = [&](void* dest,size_t size){
        memcpy(dest,buffer+offset,size);
        offset+= size;
    };

    read(&free_space,sizeof(free_space));
    read(&page_id,sizeof(page_id));

    return offset;
}

void free_space_manager::update_available_space(uint file_id,uint page_id,size_t available_space){
    if(page_location.find(file_id) != page_location.end() && page_location[file_id].find(page_id) != page_location[file_id].end()){
        auto page_it = page_location[file_id][page_id];
        
        PF_FSS[file_id].erase(page_it);
        page_location[file_id][page_id]  = PF_FSS[file_id].insert({available_space,page_id}).first;
        std::cout<<available_space<<std::endl;
    }
    else {
        std::cout<<"in add "<<available_space<<std::endl;
        add_page_space(file_id,page_id,available_space);
    }
}

void free_space_manager::add_page_space(uint file_id,uint page_id,size_t available_space){
    page_location[file_id][page_id]  = PF_FSS[file_id].insert({available_space,page_id}).first;
}

int free_space_manager::get_page_with_available_space(size_t required_space,uint file_id){
    auto it = PF_FSS[file_id].lower_bound({required_space,0});
    
    for(auto& v:PF_FSS[file_id]){
        std::cout<<v.free_space<<" "<<v.page_id<<std::endl;
    }

    return (it == PF_FSS[file_id].end()?-1:it->page_id);
}