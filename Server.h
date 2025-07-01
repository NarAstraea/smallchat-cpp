#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include "Client.h"
#include "ChatState.h"
#include "ChatlibEx.h"
#include "ThreadPool.h"


class Server{
    public:
    /*
    *@brief 
    *@param 1: Set max num of the client.(Default:100)
    *@param 2: Set server port.(Default:7712)
    *@return void
    *
    */
    explicit Server(const int &_in_default_max_client_num = 100,const int &_in_default_server_port = 7712);
    ~Server();

    private:
    
    int max_client_num = 0;
    int server_port = 0;

    boost::asio::io_context io_context;
    std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;
    std::shared_ptr<ThreadPool> thread_pool;
    ChatlibEx Chatlib;
    ChatState chats;
    std::vector<const ChatlibEx::MessageHeader*> message_queue;

    public:
    bool runServer(int _in_client_socket=0);
    bool startAsyncTcpConnectHandler(boost::asio::io_context& io_context);
    bool startAsyncMessageHandler();
};