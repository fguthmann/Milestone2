//
// Created by fanny on 19/01/2020.
//

#ifndef MILESTONE_2_MYPARALLELSERVER_H
#define MILESTONE_2_MYPARALLELSERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <netinet/in.h>
#include <thread>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include "MyClientHandler.h"
#include "Server.h"

#define TRUE   1
#define MAX_CONNECTED_CLIENTS 10

class MyParallelServer: public server_side::Server {
    mutex mutex_lock;
public:
    virtual void open(int port, ClientHandler *clientHandler);
    virtual void stop();
    string vectorToString(vector<string> matrix);
    void thread_adapter(vector<string> data, int sd);
};


struct client_struct {
    int clientSocket;
    vector<string> data;
};


#endif //MILESTONE_2_MYPARALLELSERVER_H
