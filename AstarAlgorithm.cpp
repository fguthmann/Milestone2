//
// Created by noa on 20/01/2020.
//

#include "AstarAlgorithm.h"

vector<pair<string, double>> AstarAlgorithm::search(Searchable<string>* searchable) {
    unordered_map<string, double> currentCost, cheapestCost, heuristicCost;
    auto cell = searchable->getInitialState();
    // initial state is also the goal state
    if (searchable->isGoalState(cell)) {
        vector<pair<string, double>> finalMap;
        finalMap.push_back(make_pair(cell->getState(), cell->getCost()));
        return finalMap;
    }
    this->addToOpenList(cell);
    // initializing maps
    currentCost = initCostMap(searchable);
    cheapestCost = initCostMap(searchable);
    heuristicCost = initHeuristicCost(searchable);
    currentCost.at(cell->getState()) = heuristicCost.at(cell->getState());
    cheapestCost.at(cell->getState()) = cell->getCost();
    while (this->OpenListSize() > 0) {
        auto current = findMinOpenList(this->getOpenList());
        // reached goal
        if (searchable->isGoalState(current)) {
            MatrixSearcher::buildCostPath(MatrixSearcher::tracePath(current), searchable);
            return this->getCostPath();
        }
        MatrixSearcher::popFromOpenList(current);
        // find neighbours to current
        vector<State<string>*> adjacents = searchable->getAllPossibleStates(current);
        vector<State<string>*>::iterator it;
        for (it = adjacents.begin(); it != adjacents.end(); ++it) {
            double tmpCheapCost = cheapestCost.at(current->getState()) + (*it)->getCost();
            if (((tmpCheapCost < cheapestCost.at((*it)->getState()))
                 || (cheapestCost.at((*it)->getState()) == -1)) && ((*it)->getCost() != -1)) {
                (*it)->setFather(*current);
                cheapestCost.at((*it)->getState()) = tmpCheapCost;
                currentCost.at((*it)->getState()) = cheapestCost.at((*it)->getState())
                                                    + heuristicCost.at((*it)->getState());
                if (!isCurrentInOpenList(this->getOpenList(), *it)) {
                    this->addToOpenList(*it);
                }
            }
        }
    }
    throw "error - no path found";
}
unordered_map<string, double> AstarAlgorithm::initHeuristicCost(Searchable<string>* searchable) {
    unordered_map<string, State<string>*> tmpMap = searchable->getMap();
    unordered_map<string, double> costMap;
    double goalLinePos = this->getLinePos(searchable->getGoalState());
    double goalColPos = this->getColPos(searchable->getGoalState());
    unordered_map<string, State<string>*>::iterator it;
    //move on the map and find approximate cost of path from every vertex to goal
    for (it = tmpMap.begin(); it != tmpMap.end(); ++it) {
        double linePos = this->getLinePos(it->second);
        double colPos = this->getColPos(it->second);
        double h = abs(goalLinePos-linePos) + abs(goalColPos-colPos);
        costMap.emplace(make_pair(it->first, h));
    }
    return costMap;
}
unordered_map<string, double> AstarAlgorithm::initCostMap(Searchable<string>* searchable) {
    unordered_map<string, double> cheapMap;
    unordered_map<string, State<string>*> tmpMap = searchable->getMap();
    unordered_map<string, State<string>*>::iterator it;
    for (it = tmpMap.begin(); it != tmpMap.end(); ++it) {
        cheapMap.emplace(make_pair(it->first, -1));
    }
    return cheapMap;
}

State<string> *AstarAlgorithm::findMinOpenList(priority_queue<State<string>*> openList) {
State<string>* it = NULL;
while (!openList.empty()) {
it = openList.top();
openList.pop();
}
return it;
}

bool AstarAlgorithm::isCurrentInOpenList(priority_queue<State<string>*> list, State<string> *current) {
while (!list.empty()) {
auto it = list.top();
if (it->Equals(*current)) {
return true;
}
list.pop();
}
return false;
}