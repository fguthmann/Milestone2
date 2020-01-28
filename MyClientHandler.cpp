//
// Created by fanny on 23/01/2020.
//

#include "MyClientHandler.h"
MyClientHandler::MyClientHandler() {
    this->fileCacheManager = new FileCacheManager();
}

void MyClientHandler::handleClient(vector<string> data, int socketClient) {
    string solution;
    string problem = vectorToString(data);
    if (this->fileCacheManager->findSolution(problem)) {
        string name = vectorToString(data);
        name += "_sol.txt";
        fstream file;
        file.open(this->fileCacheManager->get(name), ios::in | ios::binary);
        if (!file) {
            throw "Error - file didn't open";
        }
        getline(file, solution);
        file.close();
        //The solution need to be calculated
    } else {
        // create file for matrix
        vector<string> mat;
        mat.assign(data.begin(), data.end()-2);
        this->fileCacheManager->createProblemFile(vectorToString(mat));
        this->solver = new MatrixSolver();
        solution = this->solver->solve(data);
        // create file for solution
        this->fileCacheManager->insertSolution(vectorToString(mat), solution);
    }
    //Close the socket and mark as 0 in list for reuse
    auto rel = write(socketClient, solution.c_str(), solution.size() + 1);
    if (rel < 0) {
        throw "Error writing to socket";
    }
}

string MyClientHandler::vectorToString(vector<string> matrix) {
    string s = "";
    vector<string>::iterator it;
    for (it = matrix.begin(); it != matrix.end(); ++it) {
        s += (*it);
        //s += "\n";
    }
    return s;
}