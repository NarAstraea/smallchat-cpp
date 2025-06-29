#pragma once
#include <iostream>

class Client{
    public:
    explicit Client();
    ~Client();

    private:
    int client_socket = 0;
    std::string nickname = "";
};