//
// Created by fanny on 19/01/2020.
//

//https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/
#include "MyParallelServer.h"

void MyParallelServer::open(int port, ClientHandler *clientHandler)
{
    int opt = TRUE;
    int master_socket , addrlen , new_socket , client_socket[30], activity, i , valread , sd;
    thread clientTh[MAX_CONNECTED_CLIENTS];
    int max_sd;
    struct sockaddr_in address;
    char buffer[1025];  //data buffer of 1K

    //set of socket descriptors
    fd_set readfds;
    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < MAX_CONNECTED_CLIENTS; i++)
    {
        client_socket[i] = 0;
    }

    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        throw "socket failed";
    }

    //set master socket to allow multiple connections ,
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        throw "setsockopt";
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    //bind the socket to localhost port
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        throw "bind failed";
    }
    printf("Listener on port %d \n", port);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, MAX_CONNECTED_CLIENTS) < 0)
    {
        throw "listen";
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    cout << "Waiting for connections ...";

    while(TRUE)
    {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add child sockets to set
        for ( i = 0 ; i < MAX_CONNECTED_CLIENTS ; i++)
        {
            //socket descriptor
            sd = client_socket[i];

            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);

            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL ,so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno != EINTR))
        {
            cout << "select error" << endl;
        }

        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
            {
                throw "accept";
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket ,
                    inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

            //add new socket to array of sockets
            for (i = 0; i < MAX_CONNECTED_CLIENTS; i++)
            {
                //if position is empty
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);
                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < MAX_CONNECTED_CLIENTS; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET( sd , &readfds))
            {
               /* //Check if it was for closing , and also read the incoming message
                if ((valread = read( sd , buffer, 1024)) == 0)
                {
                    //Buffer contain informations

                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    client_socket[i] = 0;
                }
                }
                else
                {*/
                   vector<string> data;
                   string solution;
                   while (true) {
                       read(sd, buffer, sizeof(buffer));
                       string endString = buffer;
                       auto it = endString.find("\n");
                       string line = endString.substr(0, it);

                       if (line.find("end") != string::npos) {
                        //   thread clienth(&MyParallelServer::thread_adapter, this, data, sd);
                        clientHandler->handleClient(data, sd);
                           cout << "finish thread " << sd  << " " << client_socket[i] << endl;
                           close(sd);
                           client_socket[i] = 0;
                           break;
                       } else {
                           data.push_back(line);
                       }
                   }
            }
        }
    }
}

void MyParallelServer::thread_adapter(vector<string> data, int sd) {
  /*  struct client_struct *argStructP = (client_struct*)arg;
    struct client_struct argStruct = *argStructP;
    delete argStructP;*/
    mutex_lock.lock();
    MyClientHandler *client = new MyClientHandler();
    client->handleClient(data, sd);
    mutex_lock.unlock();

}

void MyParallelServer::stop() {
}

string MyParallelServer::vectorToString(vector<string> matrix) {
    string s = "";
    vector<string>::iterator it;
    for (it = matrix.begin(); it != matrix.end(); ++it) {
        s += (*it);
        //s += "\n";
    }
    return s;
}