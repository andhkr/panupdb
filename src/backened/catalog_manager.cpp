#include "include/backened/catalog_manager.hpp"
#include "include/backened/page.hpp"

std::string get_filename_without_extension(const std::string& path) {
    // Find last '/' or '\\'
    size_t last_slash = path.find_last_of("/\\");
    std::string filename = (last_slash == std::string::npos) ? path : path.substr(last_slash + 1);

    // Find last dot (.)
    size_t last_dot = filename.find_last_of('.');
    if (last_dot == std::string::npos)
        return filename;  // no extension

    return filename.substr(0, last_dot);  // strip extension
}

std::pair<file_type,std::string> get_tablename_and_type(const std::string& path) {
    // Find last '/' or '\\'
    size_t last_slash = path.find_last_of("/\\");
    std::string filename = (last_slash == std::string::npos) ? path : path.substr(last_slash + 1);

    // Find last dot (.)
    size_t last_dot = filename.find_last_of('.');
    std::string f_Type = filename.substr(last_dot+1);
    file_type ftype;
    if(f_Type == "cat"){
        ftype = CATALOG;
    }else if(f_Type == "df"){
        ftype = DATA;
    }else{
        ftype = INDEX;
    }

    return {ftype,filename.substr(0,last_dot)};  // strip extension
}

/*for file_id and file_name lookup*/
std::string file_id_filename_hash_table = "id_name.cat";

catalog_file_header::catalog_file_header(){
    magic_number = Magic_Number::CATALOG;
    page_counts = 0;
    free_page_list = page_size;
    columns_ct = 0;
    this->cat_id = 0;
}

catalog_file_header::catalog_file_header(uint cat_id){
    magic_number = Magic_Number::CATALOG;
    page_counts = 0;
    free_page_list = page_size;
    columns_ct = 0;
    this->cat_id = cat_id;
}

size_t catalog_file_header::serialise(char* buffer){
    size_t offset = 0;
    auto write = [&](void* src,size_t size){
        memcpy(buffer+offset,src,size);
        offset += size;
    };

    write(&magic_number,sizeof(magic_number));
    write(&page_counts,sizeof(page_counts));
    write(&free_page_list,sizeof(free_page_list));
    write(&columns_ct,sizeof(columns_ct));
    write(&cat_id,sizeof(cat_id));
    return offset;
}

size_t catalog_file_header::deserialise(const char* buffer){
    size_t offset = 0;
    auto read = [&](void* dest,size_t size){
        memcpy(dest,buffer+offset,size);
        offset+=size;
    };
    read(&magic_number,sizeof(magic_number));
    read(&page_counts,sizeof(page_counts));
    read(&free_page_list,sizeof(free_page_list));
    read(&columns_ct,sizeof(columns_ct));
    read(&cat_id,sizeof(cat_id));
    return offset;
}

size_t catalog_file_header::get_total_object_size(){
    size_t total = sizeof(magic_number); 
    total+= sizeof(page_counts);
    total+= sizeof(free_page_list);
    total+= sizeof(columns_ct);
    total+= sizeof(cat_id);
    return total;
}


/*
page_id of header will be zero,
page_id will be increasing order and incresed by 1
*/

catalog_manager::catalog_manager(){
    file_id_filename_lookup[0]=database_path +  file_id_filename_hash_table;
    load_file_lookup();
}

void catalog_manager::load_file_lookup() {
    // --- Step 1: Read the lookup file header from page 0 ---
    cached_page* header_page = buffer_pool_manager.get_page(0, 0);
    catalog_file_header lookup_hdr;
    lookup_hdr.deserialise(header_page->_c_page);
    uint total_pages = lookup_hdr.page_counts;

    // --- Step 2: Deserialize all (file_id → filename) entries from pages 1..total_pages ---
    for (uint page_id = 1; page_id < total_pages; ++page_id) {
        cached_page* page = buffer_pool_manager.get_page(0, page_id);

        // Deserialize the page header to get offsets
        page_header pg_hdr;
        pg_hdr.deserialise(page->_c_page);

        char* page_buf = page->_c_page;
        // The slot array runs from start_offset up to curr_offset
        char* slot_ptr = page_buf + pg_hdr.start_offset;
        char* slot_end = page_buf + pg_hdr.curr_offset;

        // Walk through each slot entry in this page
        while (slot_ptr < slot_end) {
            slot slot_meta;
            size_t slot_bytes = slot_meta.deserialise(slot_ptr);
            slot_ptr += slot_bytes;

            // Now read the id_name row at row_offset
            char* row_ptr = page_buf + slot_meta.row_offset;
            id_name file_entry;
            file_entry.deserialise(row_ptr);

            // Insert into the in-memory lookup map
            file_id_filename_lookup[file_entry.file_id] = file_entry.file_name;
        }
    }

    // --- Step 3: Load each table’s catalog (skip the id_name lookup itself) ---
    for (const auto& [file_id, path] : file_id_filename_lookup) {
        std::pair<file_type,std::string> type_name = get_tablename_and_type(path);
        if(type_name.first == CATALOG){
            if (type_name.second == "id_name") {
                continue;  // skip our own lookup metadata file
            }
            load_catalog_file(file_id,type_name.second);
        }
        else if (type_name.first == INDEX){
            /*load index file*/
        }else {
            /*load data file header or other file in near future*/
        }
        
    }
}


// /*it will table object initialised by query executor then catalog manager
// will create metadata file for this and write relevant data and then create datafile
// (file for data of table) and initilaise that header*/
void catalog_manager::create_table(table* obj) {
    // --- Step 1: Create and initialize the datafile for this table ---
    uint data_file_id = get_file_id();
    std::string datafile_name = database_path + "datafile/" + obj->table_name + ".df";
    file_id_filename_lookup[data_file_id] = datafile_name;

    // Pull page 0 of the new datafile to write its header
    cached_page* data_header_page = buffer_pool_manager.get_page(data_file_id, 0);
    data_header_page->dirty     = true;
    data_header_page->pin_unpin = true;

    datafile_header data_hdr(data_file_id, obj->table_name);
    data_hdr.serialise(data_header_page->_c_page);

    data_header_page->pin_unpin = false;


    // --- Step 2: Create and initialize the catalog file for this table ---
    uint catalog_file_id = get_file_id();
    std::string catalog_name = database_path + "catalog/" + obj->table_name + ".cat";
    file_id_filename_lookup[catalog_file_id] = catalog_name;

    // Pull page 0 of the new catalog file to write its header later
    cached_page* catalog_header_page = buffer_pool_manager.get_page(catalog_file_id, 0);
    catalog_header_page->dirty     = true;
    catalog_header_page->pin_unpin = true;

    // Register this table object in in-memory table_list
    catalog_file_list[obj->table_name] = obj;


    // --- Step 3: Write all columns (and their metadata) into catalog file pages ---
    size_t numColumns = obj->columns.size();
    size_t nextColumnIndex = 0;
    uint   page_id = 1;  // we will start writing column‐descriptors on page 1

    while (nextColumnIndex < numColumns) {
        // Grab a fresh page for catalog page page_id
        cached_page* page = buffer_pool_manager.get_page(catalog_file_id, page_id);
        page->dirty     = true;
        page->pin_unpin = true;

        page_header hdr(page_id);
        char*       payload = page->_c_page;

        // Fill as many columns as will fit on this page
        while (nextColumnIndex < numColumns) {
            table_column* column    = obj->columns[nextColumnIndex];
            size_t        rowSize   = column->get_total_sizeof_object();
            size_t        slotSize  = (2 * sizeof(size_t)); // offset + size fields

            // Check: do we have room for slotMeta + rowData?
            // Total bytes needed = slotSize + rowSize
            //
            // free space is from curr_offset ... free_space_start_marker (exclusive)
            // so the condition becomes:
            if ((hdr.curr_offset + slotSize + rowSize) <= hdr.free_space_start_marker) {
                // 1) Compute where to write the column‐row data:
                size_t rowOffset = hdr.free_space_start_marker - rowSize;
                column->serialise(payload + rowOffset);

                // 2) Prepare slot metadata (rowOffset, rowSize), then write it at curr_offset
                slot rowMeta(rowOffset, rowSize);
                size_t slotBytesWritten = rowMeta.serialise(payload + hdr.curr_offset);

                // 3) Advance header markers
                hdr.free_space_start_marker = rowOffset;
                hdr.curr_offset += slotBytesWritten;

                ++nextColumnIndex;
            }
            else {
                // Not enough room for this column on this page → finalize and move on
                break;
            }
        }

        // Serialize the page_header into the first bytes of payload
        hdr.serialise(page->_c_page);
        page->pin_unpin = false;

        ++page_id;  // next page in the catalog file (if any columns remain)
    }


    // --- Step 4: Write the catalog file’s own file header on page 0 ---
    catalog_file_header cat_hdr(catalog_file_id);
    cat_hdr.page_counts = page_id ; // number of catalog pages used (including header page)

    // If the header object itself fits in one page, write it to page 0
    if (cat_hdr.get_total_object_size() <= page_size) {
        cat_hdr.serialise(catalog_header_page->_c_page);
    }
    catalog_header_page->pin_unpin = false;
}

void catalog_manager::load_catalog_file(uint file_id,std::string& table_name) {
    // --- Step 1: Read the catalog file header from page 0 ---
    cached_page* header_page = buffer_pool_manager.get_page(file_id, 0);
    catalog_file_header cat_hdr;
    cat_hdr.deserialise(header_page->_c_page);
    uint data_pages = cat_hdr.page_counts;  // number of pages

    // Prepare a new table object to fill
    table* loaded_table = new table;
    loaded_table->table_name = table_name;

    // --- Step 2: Loop over each data page (1 .. data_pages) --- (excluding header page)
    for (uint page_id = 1; page_id < data_pages; ++page_id) {
        cached_page* page = buffer_pool_manager.get_page(file_id, page_id);

        // Deserialize the page header to find slot array bounds
        page_header pg_hdr;
        pg_hdr.deserialise(page->_c_page);

        char* page_buf  = page->_c_page;
        char* slot_ptr  = page_buf + pg_hdr.start_offset;
        char* slot_end  = page_buf + pg_hdr.curr_offset;

        // Walk through all slots on this page
        while (slot_ptr < slot_end) {
            slot slot_meta;
            size_t bytes_slot = slot_meta.deserialise(slot_ptr);
            slot_ptr += bytes_slot;

            char* row_ptr = page_buf + slot_meta.row_offset;
            table_column* column = new table_column;
            column->deserialise(row_ptr);
            loaded_table->columns.push_back(column);
        }
    }

    // --- Step 3: Store the fully loaded table in memory ---
    catalog_file_list[table_name] = loaded_table;
}

uint catalog_manager::get_file_id(){
    return ++file_id;
}

// void catalog_manager::database_query(std::string& cmd){
//     if(cmd.substr(0,2)=="/d"){
//         std::string table_name = cmd.substr(2);
//         table* tbl = table_list[table_name];
//         tbl->print();
//     }
// }

void catalog_manager::write_file_lookup() {
    // Page 0 is reserved for the lookup‐file header
    uint page_id = 0;
    cached_page* header_page = buffer_pool_manager.get_page(0, page_id);
    header_page->dirty     = true;
    header_page->pin_unpin = true;

    // Iterate over every (file_id → filename) pair
    auto it = file_id_filename_lookup.begin();
    auto end = file_id_filename_lookup.end();

    // Starting at page 1, write id_name entries until we exhaust the map
    while (it != end) {
        ++page_id;
        cached_page* page = buffer_pool_manager.get_page(0, page_id);
        page->dirty     = true;
        page->pin_unpin = true;

        page_header hdr(page_id);
        char*       buf = page->_c_page;

        // Fill as many id_name rows as will fit on this page
        while (it != end) {
            uint    file_id   = it->first;
            const std::string& filename = it->second;
            id_name entry(file_id, filename);

            size_t entry_size = entry.get_total_sizeof_object();      // bytes needed to store (file_id + filename)
            size_t slot_size  = slot().get_sizeof_object();           // bytes needed for slot metadata

            // Check: can we pack both slot metadata and row data without overflow?
            // Total needed = slot_size + entry_size,
            // and free bytes run from hdr.curr_offset up to hdr.free_space_start_marker.
            if ((hdr.curr_offset + slot_size + entry_size) <= hdr.free_space_start_marker) {
                // 1) Compute where to place the row data (at end of free space)
                size_t row_offset = hdr.free_space_start_marker - entry_size;
                entry.serialise(buf + row_offset);

                // 2) Prepare and write slot metadata at curr_offset
                slot row_meta(row_offset, entry_size);
                size_t written = row_meta.serialise(buf + hdr.curr_offset);

                // 3) Update header’s free‐space markers
                hdr.free_space_start_marker = row_offset;
                hdr.curr_offset += written;

                ++it;
            } else {
                // No more room for this entry → finish this page
                break;
            }
        }

        // Serialize the page_header into the first bytes of buf
        hdr.serialise(buf);
        page->pin_unpin = false;
    }

    // Now write the lookup file’s header (page 0)
    catalog_file_header lookup_hdr;
    lookup_hdr.cat_id     = 0;
    lookup_hdr.page_counts = page_id+1;  // total pages used for the lookup‐file (including header page)
    lookup_hdr.serialise(header_page->_c_page);
    header_page->pin_unpin = false;
}
