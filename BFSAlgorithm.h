//
// Created by noa on 18/01/2020.
//

#ifndef MILESTONE_2_BFSALGORITHM_H
#define MILESTONE_2_BFSALGORITHM_H

#include <list>
#include "MatrixSearcher.h"
using namespace std;

class BFSAlgorithm : public MatrixSearcher {
public:
    virtual vector<pair<string, double>> search(Searchable<string>* searchable);
    bool isInOpenQueue(queue<State<string>*> q, State<string>* s);
};


#endif //MILESTONE_2_BFSALGORITHM_H