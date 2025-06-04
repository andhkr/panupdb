#ifndef QUERY_PROCESSOR_HPP
#define QUERY_PROCESSOR_HPP
#include "ast.hpp"
#include "constraints.hpp"
#include "backened/table.hpp"
#include "backened/catalog_manager.hpp"

struct query_processor{

    query_processor()=default;

    void process_create_table(create_table* obj);
};

extern query_processor query_executor;
extern catalog_manager* catlg_man;
#endif