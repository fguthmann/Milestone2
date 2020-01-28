/*

//
// Created by noa on 17/01/2020.
//


#include "MyTestClientHandler.h"

void MyTestClientHandler::handleClient(vector<string> data, int socketClient) {
    this->solver = new StringReverser();
    string problem = vectorToString(data);
    string solution = this->solver->solve(problem);
    auto rel = write(socketClient, solution.c_str(), solution.size() + 1);
    if (rel < 0) {
        throw "error writing to socket";
    }
    close(socketClient);}

string MyTestClientHandler::vectorToString(vector<string> matrix) {
    string s = "";
    vector<string>::iterator it;
    for (it = matrix.begin(); it != matrix.end(); ++it) {
        s += (*it);
        //s += "\n";
    }
    return s;
}*/
