//
// Created by noa on 20/01/2020.
//

#ifndef MILESTONE_2_BESTFSALGORITHM_H
#define MILESTONE_2_BESTFSALGORITHM_H


#include "MatrixSearcher.h"

class BestFSAlgorithm : public MatrixSearcher {
    virtual vector<pair<string, double>> search(Searchable<string>* searchable);
    bool isCurrentInOpenList(priority_queue<State<string>*> list, State<string>* current);
    unordered_map<string, double> initCostMap(Searchable<string>* searchable);
};


#endif //MILESTONE_2_BESTFSALGORITHM_H
