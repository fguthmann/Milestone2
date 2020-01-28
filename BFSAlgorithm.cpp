//
// Created by noa on 18/01/2020.
//

#include "BFSAlgorithm.h"

vector<pair<string, double>> BFSAlgorithm::search(Searchable<string>* searchable) {
    queue<State<string>*> openQueue;
    // initialize marked map
    auto cell = searchable->getInitialState();
    // initial state is also the goal state
    if (searchable->isGoalState(cell)) {
        vector<pair<string, double>> finalMap;
        finalMap.push_back(make_pair(cell->getState(), cell->getCost()));
        return finalMap;
    }
    openQueue.push(cell);
    while (!openQueue.empty()) {
        auto x = openQueue.front();
        openQueue.pop();
        // cell is unmarked
        if (!this->isMarked(x)) {
            this->addToMarkedCells(x->getState());
            this->addNodeEvaluated();
        }
        // end of search
        if (searchable->isGoalState(x)) {
            MatrixSearcher::buildCostPath(MatrixSearcher::tracePath(x), searchable);
            return this->getCostPath();
        }
        // add neighbours to list
        vector<State<string>*> adjacents = searchable->getAllPossibleStates(x);
        vector<State<string>*>::iterator it;
        for (it = adjacents.begin(); it != adjacents.end(); ++it) {
            // next one is not a wall
            if (((*it)->getCost() != -1) && (!isInOpenQueue(openQueue, *it)) && !this->isMarked((*it))) {
                (*it)->setFather(*x);
                openQueue.push(*it);
            }
        }
    }
    throw "error - no path found";
}

bool BFSAlgorithm::isInOpenQueue(queue<State<string>*> q, State<string> *s) {
    State<string>* it;
    while (!q.empty()) {
        it = q.front();
        if (it->Equals(*s)) {
            return true;
        }
        q.pop();
    }
    return false;
}