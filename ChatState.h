#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <boost/asio.hpp>
#include <optional>
#include "Client.h"

class ChatState{
    public:
    explicit ChatState(const int &_in_default_max_client_num = 100);
    ~ChatState();

    private:
    int max_client_num = 0;

    int server_sock = 0;
    int client_current_num = 0;
    int client_populated = 0;
    std::vector<Client> clients;

    public:
    bool createClient(boost::asio::io_context &_in_io_context,const std::string &_in_nikename);
    std::optional<std::reference_wrapper<Client>> getClient(const int& _in_index=-1);
    std::optional<std::reference_wrapper<Client>> getClient(const std::string &_in_nickname="");
    std::optional<std::reference_wrapper<Client>> getClient(const int& _in_index=-1,const std::string &_in_nickname="");
};