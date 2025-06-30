#include "ThreadPool.h"

ThreadPool::ThreadPool(const size_t& thread_count){
    for(std::size_t i =0;i<thread_count;++i){
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
