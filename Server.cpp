#include "Server.h"

Server::Server(const int &_in_default_max_client_num,const int &_in_default_server_port):
    max_client_num(_in_default_max_client_num),
    server_port(_in_default_server_port)
{
    thread_pool = std::make_shared<ThreadPool>(_in_default_max_client_num);
    chats=ChatState();
    Chatlib = ChatlibEx();
    acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(io_context,tcp::endpoint(boost::asio::ip::tcp::v4(),_in_default_server_port));


}

Server::~Server(){}

bool Server::runServer(int _in_client_socket){
    std::string nickname;
    std::cout<<"Please enter username:";
    std::cin>>nickname;

    chats.createClient(io_context,nickname);
    chats.getClient(nickname);

    Chatlib.TCPConnect(io_context,acceptor,thread_pool,message_queue);
    startAsyncTcpConnectHandler(io_context);
    return 0;
}
bool Server::startAsyncTcpConnectHandler(boost::asio::io_context& io_context){
    thread_pool->submit(std::function<void()>([this,&io_context]{
        for(;;){
            io_context.run();
        }
    }));
    return 0;
}