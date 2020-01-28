//
// Created by fanny on 19/01/2020.
//

#include <vector>
#include <string>
#include <iostream>
#include "Server.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "MatrixSolver.h"
#include "MyParallelServer.h"
#include "MyClientHandler.h"
#include "DFSAlgorithm.h"


#ifndef MILESTONE_2_MAIN_H
#define MILESTONE_2_MAIN_H

namespace boot {

    class Main {
    public:
        void main(int port) {
             server_side::Server *server = new MyParallelServer();
             ClientHandler *client = new MyClientHandler();
             server->open(port, client);
             delete(server);
             delete(client);
           /* vector<string> data;
            vector<string> mat;
            string line;
            fstream file;
            file.open("matrix_test.txt", ios::in);
            while (getline(file, line)) {
                if (line == "end") {
                    break;
                }
                data.push_back(line);
            }
            mat.assign(data.begin(), data.end()-2);
            Searchable<string>* matrix = new Matrix(mat, *prev(prev(data.end())), *prev(data.end()));
            MatrixSearcher* algo = new AstarAlgorithm();
            unordered_map<string, double> sol = algo->search(matrix);
            FileCacheManager *fileCacheManager = new FileCacheManager();
            unordered_map<string, double>::iterator it;
            for (it = sol.begin(); it != sol.end(); ++it) {
                cout << it->first<< " " << it->second << endl;
            }*/
        }
    };
}

#endif //MILESTONE_2_MAIN_H