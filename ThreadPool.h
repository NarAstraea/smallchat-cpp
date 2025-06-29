#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <future>
#include <condition_variable>

class ThreadPool{
    public:
    explicit ThreadPool(const size_t& thread_count=2);
    ~ThreadPool();

    
    template<class T,class ... Args>
    auto submit(T&& _in_class,Args&&... _in_args) -> std::future<decltype(_in_class(_in_args...))>;
    
    private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop{false};

    void worker();

};