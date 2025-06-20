#include "include/thread_pool.hpp"
    
__thread_pool_::__thread_pool_(int thread_cts):num_threads(thread_cts),stop(false){
    threads.reserve(num_threads);

    for(int i = 0;i<thread_cts;++i){
        threads.emplace_back(
            [this]{
                while (true){
                    std::function<void()> task;
                    {
                        std::unique_lock lock(queue_mutex);
                        cv.wait(lock,[this](){return stop || !task_queue.empty();});

                        if(stop) return;

                        task = std::move(task_queue.front());
                        task_queue.pop();
                    }
                    task();
                }
                
            }
        );
    }
}

__thread_pool_::~__thread_pool_(){
    {
        std::unique_lock lk(queue_mutex);
        stop = true;
    }
    cv.notify_all();
    for(int i = 0;i<num_threads;++i){
        if(threads[i].joinable()) threads[i].join();
    }
}
