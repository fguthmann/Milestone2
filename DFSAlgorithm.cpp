//
// Created by noa on 23/01/2020.
//

#include "DFSAlgorithm.h"

vector<pair<string, double>> DFSAlgorithm::search(Searchable<string>* searchable) {
    stack<State<string>*> openStack;
    // initialize marked map
    auto cell = searchable->getInitialState();
    // initial state is also the goal state
    if (searchable->isGoalState(cell)) {
        vector<pair<string, double>> finalMap;
        finalMap.push_back(make_pair(cell->getState(), cell->getCost()));
        return finalMap;
    }
    openStack.push(cell);
    while (!openStack.empty()) {
        auto x = openStack.top();
        openStack.pop();
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
            if (((*it)->getCost() != -1) && (!isInOpenStack(openStack, *it)) && !this->isMarked((*it))) {
                (*it)->setFather(*x);
                openStack.push(*it);
            }
        }
    }
    throw "error - no path found";
}

bool DFSAlgorithm::isInOpenStack(stack<State<string> *> stack, State<string> *s) {
    State<string>* it;
    while (!stack.empty()) {
        it = stack.top();
        if (it->Equals(*s)) {
            return true;
        }
        stack.pop();
    }
    return false;
}