//
// Created by fanny on 19/01/2020.
//

#ifndef MILESTONE_2_SERVER_H
#define MILESTONE_2_SERVER_H

#include <iostream>
#include <fstream>
#include "ClientHandler.h"
using namespace std;
namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler *clientHandler) = 0;
        virtual void stop() = 0;
    };
}


#endif //MILESTONE_2_SERVER_H
