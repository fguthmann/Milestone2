//
// Created by noa on 20/01/2020.
//

#include "BestFSAlgorithm.h"

vector<pair<string, double>> BestFSAlgorithm::search(Searchable<string>* searchable) {
    unordered_map<string, double> costMap = initCostMap(searchable);
    auto cell = searchable->getInitialState();
    // initial state is also the goal state
    if (searchable->isGoalState(cell)) {
        vector<pair<string, double>> finalMap;
        finalMap.push_back(make_pair(cell->getState(), cell->getCost()));
        return finalMap;
    }
    this->addToOpenList(cell);
    while (this->OpenListSize() > 0) {
        auto current = this->popOpenList();
        this->addToMarkedCells(current->getState());
        // end of path
        if (searchable->isGoalState(current)) {
            MatrixSearcher::buildCostPath(MatrixSearcher::tracePath(current), searchable);
            return this->getCostPath();
        }
        vector<State<string>*> adjacents = searchable->getAllPossibleStates(current);
        vector<State<string>*>::iterator it;
        for (it = adjacents.begin(); it != adjacents.end(); ++it) {
            if ((!isCurrentInOpenList(this->getOpenList(), *it)) && (!this->isMarked(*it)) && ((*it)->getCost() != -1)) {
                (*it)->setFather(*current);
                this->addToOpenList(*it);
                this->addToMarkedCells((*it)->getState());
                this->addNodeEvaluated();
                costMap.at((*it)->getState()) = (*it)->getCost() + current->getCost();
            }
        }
    }
    throw "error - no path found";
}

unordered_map<string, double> BestFSAlgorithm::initCostMap(Searchable<string>* searchable) {
    unordered_map<string, double> cheapMap;
    unordered_map<string, State<string>*> tmpMap = searchable->getMap();
    auto it = tmpMap.begin();
    cheapMap.emplace(make_pair(it->first, it->second->getCost()));
    it++;
    for ( ; it != tmpMap.end(); ++it) {
        cheapMap.emplace(make_pair(it->first, -1));
    }
    return cheapMap;
}

bool BestFSAlgorithm::isCurrentInOpenList(priority_queue<State<string> *> list, State<string> *current) {
    while (!list.empty()) {
        auto it = list.top();
        if (it->Equals(*current)) {
            return true;
        }
        list.pop();
    }
    return false;
}