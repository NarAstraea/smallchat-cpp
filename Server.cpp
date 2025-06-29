#include "Server.h"

Server::Server(const int &_in_default_max_client_num,const int &_in_default_server_port):
    max_client_num(_in_default_max_client_num),
    server_port(_in_default_server_port),
    thread_pool(ThreadPool(_in_default_max_client_num))
{
    
}

Server::~Server(){}

Client Server::createClient(int _in_client_socket){
    std::string nickname;
    std::cout<<"enter username:";
    std::cin>>nickname;
    
    Chatlib.TCPConnect("");

    return Client();
}