//
// Created by noa on 23/01/2020.
//

#ifndef MILESTONE_2_DFSALGORITHM_H
#define MILESTONE_2_DFSALGORITHM_H

#include <stack>
#include "MatrixSearcher.h"

class DFSAlgorithm : public MatrixSearcher {
    virtual vector<pair<string, double>> search(Searchable<string>* searchable);
    bool isInOpenStack(stack<State<string>*> stack, State<string>* s);
};

#endif //MILESTONE_2_DFSALGORITHM_H