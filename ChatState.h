#pragma once
#include <iostream>
#include <vector>
#include <memory>
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
    std::vector<std::unique_ptr<Client>> clients;
};