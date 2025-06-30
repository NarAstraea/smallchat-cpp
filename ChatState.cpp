#include "ChatState.h"

ChatState::ChatState(const int &_in_default_max_client_num):max_client_num(_in_default_max_client_num){
    /*Initialize clients content.*/

}

ChatState::~ChatState(){
    clients.clear();
}
bool ChatState::createClient(boost::asio::io_context &_in_io_context,const std::string &_in_nikename){
    clients.emplace_back(Client(_in_io_context,_in_nikename));

}

std::optional<std::reference_wrapper<Client>> ChatState::getClient(const int& _in_index){
    if(_in_index<0){
        //error
        std::cerr<<"[ChatState.cpp]The index format provided for search was incorrect."<<std::endl;
        return std::nullopt;
    }else{
        return std::ref(clients.at(0));
    }
}
std::optional<std::reference_wrapper<Client>> ChatState::getClient(const std::string &_in_nickname){
    if(_in_nickname.empty()){
        //error
        std::cerr<<"[ChatState.cpp]The nickname format provided for search was incorrect."<<std::endl;
        return std::nullopt;
    }else{
        for(Client &t : clients){
            if(t.nickname == _in_nickname)
                return std::ref(t);
        }
        //error
        std::cerr<<"[ChatState.cpp]Specified nickname not found."<<std::endl;
    }
}
std::optional<std::reference_wrapper<Client>> ChatState::getClient(const int& _in_index,const std::string &_in_nickname){
    if(_in_index<0 || _in_nickname.empty()){
        //error
        std::cerr<<"[ChatState.cpp]The index or nickname format provided for search was incorrect."<<std::endl;
        return std::nullopt;
    }else if(_in_index >=0){
        return std::ref(clients.at(0));
    }else{
        for(Client &t : clients){
            if(t.nickname == _in_nickname)
                return std::ref(t);
        }
        //error
        std::cerr<<"[ChatState.cpp]Specified nickname not found."<<std::endl;
    }
}