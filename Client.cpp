#include "Client.h"

Client::Client(boost::asio::io_context& _in_io_context,const std::string &_in_nikename):nickname(_in_nikename){
    client_socket = std::make_unique<boost::asio::ip::tcp::socket>(_in_io_context);
}
Client::~Client(){}

bool Client::setNickname(std::string _in_nickname){
    this->nickname = _in_nickname;
}
std::shared_ptr<boost::asio::ip::tcp::socket>& Client::getClientSocket(){
    return client_socket;
}