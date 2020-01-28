//
// Created by fanny on 19/01/2020.
//

#ifndef MILESTONE_2_MYSERIALSERVER_H
#define MILESTONE_2_MYSERIALSERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <limits>
#include "Server.h"
#include "StringReverser.h"
#include "MyTestClientHandler.h"

#define MAX_CONNECTED_CLIENTS 10


class MySerialServer: public server_side::Server {
public:
    virtual void open(int port, ClientHandler *clientHandler);
    virtual void stop();
};


#endif //MILESTONE_2_MYSERIALSERVER_H
