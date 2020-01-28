//
// Created by noa on 19/01/2020.
//

#include "MatrixSearcher.h"

State<string>* MatrixSearcher::popOpenList() {
    this->evaluatedNodes++;
    State<string>* state = this->openList.top();
    this->openList.pop();
    return state;
}

void MatrixSearcher::popFromOpenList(State<string>* current) {
    priority_queue<State<string>*> tmp;
    while (!this->openList.top()->Equals(*current)) {
        auto item = this->openList.top();
        this->openList.pop();
        tmp.push(item);
    }
    // pop current
    this->popOpenList();
    // return values
    while (!tmp.empty()) {
        auto item = tmp.top();
        tmp.pop();
        this->openList.push(item);
    }
}

int MatrixSearcher::OpenListSize() {
    return this->openList.size();
}

int MatrixSearcher::getNumberOfNodesEvaluated() {
    return this->evaluatedNodes;
}

void MatrixSearcher::addNodeEvaluated() {
    this->evaluatedNodes++;
}

priority_queue<State<string>*> MatrixSearcher::getOpenList() {
    return this->openList;
}

void MatrixSearcher::addToOpenList(State<string>* cell) {
    this->openList.push(cell);
}

vector<string> MatrixSearcher::getPath() {
    return this->marked_cells;
}

void MatrixSearcher::addToMarkedCells(string cell) {
    this->marked_cells.push_back(cell);
}

bool MatrixSearcher::isMarked(State<string> *s) {
    vector<string>::iterator it;
    for (it = marked_cells.begin(); it != marked_cells.end(); ++it) {
        // s is marked
        if (!(*it).compare(s->getState())) {
            return true;
        }
    }
    return false;
}

double MatrixSearcher::getLinePos(State<string>* s) {
    auto it = s->getState().find(",");
    string temp = s->getState();
    return stod(temp.substr(0, it));
}

double MatrixSearcher::getColPos(State<string>* s) {
    auto it = s->getState().find(",");
    string temp = s->getState();
    return stod(temp.substr(it+1));
}

vector<string> MatrixSearcher::tracePath(State<string>* current) {
    State<string>* tmp = current;
    vector<string> path;
    list<string> tmpPath;
    // finding path from goal to start
    while (tmp != NULL) {
        tmpPath.push_back(tmp->getState());
        tmp = tmp->getFather();
    }
    // copy list to vector
    while (!tmpPath.empty()) {
        path.push_back(tmpPath.back());
        tmpPath.pop_back();
    }
    return path;
}

vector<pair<string, double>> MatrixSearcher::getCostPath() {
    return this->costPath;
}

void MatrixSearcher::buildCostPath(vector<string> path, Searchable<string> *searchable) {
    unordered_map<string, State<string>*> tmpMap = searchable->getMap();
    vector<string>::iterator it;
    for (it = path.begin(); it != path.end(); ++it) {
        string name = *it;
        State<string>* state = tmpMap.at(name);
        // initialize pair with cell's cost
        unordered_map<string, State<string>*>::iterator tmpIt;
        State<string> tmpState = *state;
        // add costs of previous cells
        int sumCost = findPrevSumCost(path, tmpMap, name);
        this->costPath.push_back(make_pair(name, sumCost));
    }
}

vector<pair<string, double>>::iterator MatrixSearcher::findCostInPath(string name, double cost) {
    std::vector<pair<string, double>>::iterator it;
    for (it = this->costPath.begin(); it != this->costPath.end(); ++it) {
        if (it->first == name && it->second == cost) {
            return it;
        }
    }
    return it;
}

int MatrixSearcher::findPrevSumCost(vector<string> path, unordered_map<string, State<string> *> tmpMap, string name) {
    vector<string>::iterator it;
    int sum = 0;
    for (it = path.begin(); it != path.end(); ++it) {
        sum += tmpMap.find(*it)->second->getCost();
        if (*it == name) {
            return sum;
        }
    }
    return -1;
}

