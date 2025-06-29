#include "ChatState.h"

ChatState::ChatState(const int _in_default_max_client_num):max_client_num(_in_default_max_client_num){
    /*Initialize clients content.*/
    for(int i =0;i< max_client_num;++i){
        clients.push_back(std::make_unique<Client>());
    }
}

ChatState::~ChatState(){
    clients.clear();
}