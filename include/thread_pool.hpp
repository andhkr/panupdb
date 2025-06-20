#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <functional>

struct __thread_pool_{
    int num_threads;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> task_queue;
    bool stop;
    std::mutex queue_mutex;
    std::condition_variable cv;
    
    __thread_pool_(int thread_cts);

    template<typename Func, typename... Args>
    auto submit_task(Func&& func, Args&&... args) -> std::future<decltype(func(args...))> {

        using return_type = decltype(func(args...));

        std::shared_ptr<std::packaged_task<return_type()>> task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<Func>(func),std::forward<Args>(args)...)
        );

        std::future<return_type> res_handle = task->get_future();

        {
            std::unique_lock lk(queue_mutex);
            if(stop){
                throw std::runtime_error("Submiting the Task when pool is stopped\n");
            }
            task_queue.emplace([task](){(*task)();});
        }
        cv.notify_one();
        return res_handle;
    }

    ~__thread_pool_();
};

#endif