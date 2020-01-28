/*
//
// Created by noa on 17/01/2020.
//

#ifndef MILESTONE_2_MYTESTCLIENTHANDLER_H
#define MILESTONE_2_MYTESTCLIENTHANDLER_H

#include <string>
#include "ClientHandler.h"
#include "MatrixSolver.h"
#include "StringReverser.h"
#include <unistd.h>

using namespace std;
class MyTestClientHandler : public ClientHandler {
Solver<string, string> *solver;
public:
    virtual void handleClient(vector<string> problem, int socketClient);
    string vectorToString(vector<string> matrix);
    };


#endif //MILESTONE_2_MYTESTCLIENTHANDLER_H
*/
