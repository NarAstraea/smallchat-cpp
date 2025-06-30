#include <iostream>
#include "Server.h"

int main(void){
    Server server = Server();
    server.runServer();

    for(;;){
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    system("pause");
    return 0;
}