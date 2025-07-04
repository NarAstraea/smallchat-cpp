#include "ChatlibEx.h"

ChatlibEx::ChatlibEx(){

}

ChatlibEx::~ChatlibEx(){

}


int ChatlibEx::TCPConnect(boost::asio::io_context& io_context,std::unique_ptr<boost::asio::ip::tcp::acceptor> &acceptor,std::shared_ptr<ThreadPool>& _in_thread_pool,std::vector<const MessageHeader*>& _in_message_queue){
    try{
        //waiting for connect
        auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context);
        acceptor->async_accept(*socket,[this,socket,&acceptor,&io_context,&_in_thread_pool,&_in_message_queue](const boost::system::error_code& ec){
            if(!ec){
                std::cout<<"Client connected from:"<< socket->remote_endpoint() << std::endl;
            }
            _in_thread_pool->submit(std::function<void()>([this,socket,&io_context,&_in_message_queue]{
                this->chatService(socket,_in_message_queue);
            }));
            
            TCPConnect(io_context,acceptor,_in_thread_pool,_in_message_queue);
        });
    }catch(std::exception &e){
        std::cerr<<"Exception:"<<std::endl;
    }
    return 0;
}

bool ChatlibEx::chatService(std::shared_ptr<boost::asio::ip::tcp::socket> _in_socket,std::vector<const MessageHeader*>& _in_message_queue){
    //cache area
    std::array<char,1024> buffer;
    boost::system::error_code error;

    try{
        boost::asio::write(*_in_socket,boost::asio::buffer(std::string("Please set nickname:")));
        std::size_t len = _in_socket->read_some(boost::asio::buffer(buffer),error);
        _in_message_queue.emplace_back(reinterpret_cast<const MessageHeader*>(buffer.data()));
        for(;;){
            std::size_t len = _in_socket->read_some(boost::asio::buffer(buffer),error);
            if(error==boost::asio::error::eof){
            std::cout<<"Connection closed by client."<<std::endl;
            break;
        }else if (error){
            throw boost::system::system_error(error);
        }

        boost::asio::write(*_in_socket,boost::asio::buffer(buffer,len));
    }
    }catch(const boost::system::system_error &e){
        std::cerr<<"system error:"<<e.what()<<std::endl;
    }
    return 0;
}