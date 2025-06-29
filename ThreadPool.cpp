#include "ThreadPool.h"

ThreadPool::ThreadPool(const size_t& thread_count){
    for(size_t i =0;i<thread_count;++i){
        workers.emplace_back([this]{this->worker();});
    }
}

ThreadPool::~ThreadPool(){
    stop.store(true);
    condition.notify_all();
    for(std::thread &t:workers){
        if(t.joinable())
            t.join();
    }
}

void ThreadPool::worker(){
    while(!stop){
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock,[this]{return stop || !tasks.empty();});

            if(stop && tasks.empty())
                return;

            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}

template<class T,class... Args>
auto ThreadPool::submit(T&& _in_t,Args&&... _in_args) 
-> std::future<decltype(_in_t(_in_args...))>{
    using return_type = decltype(_in_t(_in_args...));
    
    auto task_ptr = std::mask_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<T>(_in_t),std::forward<Args>(args)...)
    );
    std::future<return_type> result = task_ptr->get_future();
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        if(stop)
            throw std::runtime_error("ThreadPool is stopped.");
        tasks.emplace([task_ptr](){(*task_ptr)();});
    }
    condition.notify_one();
    return result;
}