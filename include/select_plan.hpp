#ifndef SELECT_PLAN_HPP
#define SELECT_PLAN_HPP

#include "backened/catalog_manager.hpp"
#include "select_log.hpp"
#include "thread_pool.hpp"
#define NUM_THREADS 8

using row = std::vector<datatype*>;
using batch = std::vector<row>;

extern __thread_pool_ worker_threads;

extern catalog_manager* catlg_man;

constexpr int MAX_BATCH_SIZE = 2; /*--> how many page at once*/

struct physical_op{
    std::vector<std::unique_ptr<physical_op>> children;
    virtual ~physical_op()=default;
    virtual bool next(std::future<batch>& result_hndl) = 0;
};

using physical_op_uptr = std::unique_ptr<physical_op>;

struct project_op : physical_op{
    table* tbl;
    std::vector<int> col_indx;
    std::vector<std::string> clmns;

    project_op(table* tbl,std::vector<int>& col_index,physical_op_uptr child,std::vector<std::string>& clmns);

    batch project(batch&& tbl_batch);

    bool next(std::future<batch>& res_hndl);
};

struct selection_op : physical_op{
    std::unique_ptr<condition> predicate;
    table* tbl;

    selection_op(std::unique_ptr<condition> predicate,table* tbl,physical_op_uptr child);
     
    batch select(batch&& tbl_batch);

    bool next(std::future<batch>& res_hndl);
};

struct scan_op:physical_op{
    table* tbl;
    int total_batch;
    int curr_batch;
    int last_page;

    scan_op(table* t);

    batch scan_task(uint batch_id);

    bool next(std::future<batch>& result_hndl);
};

struct query_planner{
    static physical_op_uptr plan(logical_op* loptr);
};

#endif