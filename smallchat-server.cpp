#include <iostream>
#include "Server.h"

int main(void){
    Server server = Server();
    server.createClient();

    system("pause");
    return 0;
}