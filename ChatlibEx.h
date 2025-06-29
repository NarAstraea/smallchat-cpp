#ifndef _CHATLIBEX_H_
#define _CHATLIBEX_H_

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

using boost::asio::ip::tcp;

CHATLIB_API class ChatlibEx{
    public:
    explicit ChatlibEx();
    ~ChatlibEx();

    boost::asio::io_context io_context;

    int TCPConnect(std::string addr,int _in_port = 7712);
};
#endif // CHATLIB_H