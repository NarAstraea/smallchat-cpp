#pragma once
#include <iostream>
#include <boost/asio.hpp>


class Client{
    public:
    explicit Client(boost::asio::io_context&,const std::string &_in_nikename);
    ~Client();

    private:
    std::shared_ptr<boost::asio::ip::tcp::socket> client_socket;

    public:
    std::string nickname = "";

    bool setNickname(std::string _in_nickname);
    std::shared_ptr<boost::asio::ip::tcp::socket>& getClientSocket();
};