// #include <iostream>
// #include "page.hpp"
// #include <vector>
// #include "../datatypes.hpp"
// #include "catalog_manager.hpp"

// extern catalog_manager* catlg_man;

// /*this extendible hashing will only work for unique constraint column to avoid overflow buckets
// in future for range queries B+tree will be implemented*/

// struct location_of_tuple{
//     datatype* key;
//     uint file_id;
//     uint page_id;
//     size_t slot_offset;
// };

// struct bucket{
//     uint page_id;
//     /*bucket capacity will be propertional to page_size*/
//     uint bucket_size; 
//     /*key value pair
//     key:column value 
//     value:location_of_tuple*/

//     bucket()=default;

//     bool insert(uint file_id){
//         cached_page* bucket_page = catlg_man->buffer_pool_manager.get_page(file_id,page_id);

//     }
// };


// struct header{
//     /*maximum directory entry header can contains is proportional to page_size*/        
// };

// struct extendible_hashing{
//     int global_depth=2;

// };

// struct directory{

// };

