//
// Created by noa on 19/01/2020.
//

#ifndef MILESTONE_2_MATRIXSOLVER_H
#define MILESTONE_2_MATRIXSOLVER_H

#include <string>
#include "Solver.h"
#include "Searcher.h"
#include "MatrixSearcher.h"
#include "AstarAlgorithm.h"
#include "BFSAlgorithm.h"
#include "BestFSAlgorithm.h"
#include "FileCacheManager.h"
#include "Matrix.h"

using namespace std;

class MatrixSolver : public Solver<vector<string>, string> {
    MatrixSearcher *searcher;
    Searchable<string> *searchable;
public:
    MatrixSolver();
    virtual string solve(vector<string> p);
    string findDirection(string current);
    ~MatrixSolver() {
        delete(this->searchable);
        delete(this->searcher);
    }
};


#endif //MILESTONE_2_MATRIXSOLVER_H
