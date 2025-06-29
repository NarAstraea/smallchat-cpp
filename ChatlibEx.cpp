#include "ChatlibEx.h"

ChatlibEx::ChatlibEx(){

}

ChatlibEx::~ChatlibEx(){

}

int ChatlibEx::TCPConnect(std::string addr,int _in_port){
    try{
        for(;;){
            boost::asio::ip::tcp::acceptor acceptor = boost::asio::ip::tcp::acceptor(io_context,tcp::endpoint(tcp::v4(),_in_port));
            //waiting for connect
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::cout << "Client connected from: " << socket.remote_endpoint() << std::endl;
            
            //connect cache area
            std::array<char,1024> buffer;
            boost::system::error_code error;

            for(;;){
                std::size_t len = socket.read_some(boost::asio::buffer(buffer),error);
                if(error==boost::asio::error::eof){
                    std::cout<<"Connection closed by client."<<std::endl;
                    break;
                }else if (error){
                    throw boost::system::system_error(error);
                }

                boost::asio::write(socket,boost::asio::buffer(buffer,len));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }catch(std::exception &e){
        std::cerr<<"Exception:"<<std::endl;
    }
}