#include "include/select_plan.hpp"

__thread_pool_ worker_threads(NUM_THREADS);

project_op::project_op(table* tbl,std::vector<int>& col_index,physical_op_uptr child,std::vector<std::string>& clmns):tbl(tbl),
col_indx(std::move(col_index)),clmns(std::move(clmns)){
    children.push_back(std::move(child));
}

batch project_op::project(batch&& tbl_batch){

    batch projected_tbl;

    for(auto& r:tbl_batch){
        row projected_row;
        for(int& ind: col_indx){
            projected_row.push_back(r[ind]);
        }
        projected_tbl.push_back(projected_row);
    }

    return projected_tbl;
}

bool project_op::next(std::future<batch>& res_hndl){
    std::future<batch> result;
    if(children[0]->next(result)){
        res_hndl = worker_threads.submit_task(
            [this,result=std::move(result)]() mutable{
                return this->project(std::move(result.get()));
            }
        );
        return true;
    }
    return false;
}


selection_op::selection_op(std::unique_ptr<condition> predicate,table* tbl,physical_op_uptr child):predicate(std::move(predicate)),tbl(tbl){
    children.push_back(std::move(child));
}
    
batch selection_op::select(batch&& tbl_batch){
    batch filtered_row;

    for(auto& r:tbl_batch){
        
        if(!predicate || predicate->evaluate(r,tbl)){
            filtered_row.push_back(r);
        }
    }

    return filtered_row;
}

bool selection_op::next(std::future<batch>& res_hndl){
    std::future<batch> result;
    if(children[0]->next(result)){
        res_hndl = worker_threads.submit_task(
            [this,result = std::move(result)]()mutable{
                return this->select(std::move(result.get()));
            }
        );
        return true;
    }   
    return false;
}


scan_op::scan_op(table* t):tbl(t){
    datafile_header df_hdr;
    // std::cout<<catlg_man<<std::endl;
    cached_page* c_hdr_page = catlg_man->buffer_pool_manager.get_page(tbl->table_id,0);
    c_hdr_page->pin_unpin = true;
    df_hdr.deserialise(c_hdr_page->_c_page);
    uint page_cnts = df_hdr.page_counts;
    total_batch = (page_cnts + MAX_BATCH_SIZE - 1)/MAX_BATCH_SIZE;
    curr_batch  = 1;
    last_page = page_cnts;
    c_hdr_page->pin_unpin = false;
}

batch scan_op::scan_task(uint batch_id){
    batch tpls;

    int pid = (batch_id<<1)-1;
    int end = std::min(int(pid + MAX_BATCH_SIZE),last_page);

    for(;pid<end;++pid){
        catlg_man->get_batch_of_tbl(tpls,tbl->table_id,pid);
    }

    return tpls;
}

bool scan_op::next(std::future<batch>& result_hndl){
    if(curr_batch>total_batch) return false;

    result_hndl = worker_threads.submit_task(
        [this,batch_id = curr_batch](){
            return this->scan_task(batch_id);
        }
    );

    curr_batch++;
    return true;
}

extern catalog_manager* catlg_man;

physical_op_uptr query_planner::plan(logical_op* loptr){
    switch(loptr->type){
        case SCAN:{
            table* tbl = catlg_man->catalog_file_list[static_cast<scan*>(loptr)->table_name];
            // std::cout<<tbl->table_id<<std::endl;
            return std::make_unique<scan_op>(tbl);
            break;
        }case SELECT:{
            physical_op_uptr scan_child = plan(loptr->children[0].get());
            return std::make_unique<selection_op>(std::move(static_cast<selection*>(loptr)->predicate),static_cast<scan_op*>(scan_child.get())->tbl,std::move(scan_child));
            break;
        }case PROJECT:{
            physical_op_uptr select_child = plan(loptr->children[0].get());
            std::vector<int> col_index;
            table* tbl = static_cast<selection_op*>(select_child.get())->tbl;
            std::vector<std::string> clmn_list;

            if(static_cast<projection*>(loptr)->columns_list[0]->identifier == "*"){
                for(auto& clmn : tbl->columns){
                    clmn_list.push_back(clmn->column_name);
                    col_index.push_back(tbl->index_of_col(clmn->column_name));
                }
            }else{
                for(auto& col:static_cast<projection*>(loptr)->columns_list){
                    col_index.push_back(tbl->index_of_col(col->identifier));
                }
                
                for(auto& node:static_cast<projection*>(loptr)->columns_list){
                    clmn_list.push_back(node->identifier);
                };
            }

            return std::make_unique<project_op>(tbl,col_index,std::move(select_child),clmn_list);
            break;
        }case JOIN:{

            break;
        }default:{

            break;
        }
    }
    return nullptr;
}
