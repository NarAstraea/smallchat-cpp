#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #ifdef CHATLIB_EXPORTS
    #define CHATLIB_API __declspec(dllexport)
    #else
    #define CHATLIB_API __declspec(dllimport)
    #endif
#else
    #define CHATLIB_API

#endif
#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include "ThreadPool.h"

using boost::asio::ip::tcp;

CHATLIB_API class ChatlibEx{
    public:
    explicit ChatlibEx();
    ~ChatlibEx();


    int TCPConnect(boost::asio::io_context& io_context,std::unique_ptr<boost::asio::ip::tcp::acceptor> &acceptor,std::shared_ptr<ThreadPool>& _in_thread_pool);
    bool chatService(std::shared_ptr<boost::asio::ip::tcp::socket> _in_socket);
};
