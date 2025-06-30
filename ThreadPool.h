#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <future>
#include <functional>
#include <condition_variable>

class ThreadPool{
    public:
    explicit ThreadPool(const std::size_t& thread_count=2);
    ~ThreadPool();

    
    template<class T,class ... Args>
    auto submit(T&& _in_t,Args&&... _in_args) -> std::future<decltype(_in_t(_in_args...))>{
        using return_type = decltype(_in_t(_in_args...));
    
        auto task_ptr = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<T>(_in_t),std::forward<Args>(_in_args)...)
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
    
    private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop{false};

    void worker();

};