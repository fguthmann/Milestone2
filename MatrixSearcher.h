//
// Created by noa on 19/01/2020.
//

#ifndef MILESTONE_2_MATRIXSEARCHER_H
#define MILESTONE_2_MATRIXSEARCHER_H

#include <queue>
#include <list>
#include "Searcher.h"
#include "Matrix.h"
using namespace std;

class MatrixSearcher : public Searcher<string, vector<pair<string, double>>> {
    vector<string> marked_cells;
    priority_queue<State<string>*> openList;
    vector<pair<string, double>> costPath;
    int evaluatedNodes = 0;
protected:
    State<string>* popOpenList();
    void popFromOpenList(State<string>* current);
public:
    virtual vector<pair<string, double>> search(Searchable<string>* searchable) = 0;
    int OpenListSize();
    int getNumberOfNodesEvaluated();
    void addNodeEvaluated();
    priority_queue<State<string>*> getOpenList();
    void addToOpenList(State<string>* cell);
    vector<string> getPath();
    void addToMarkedCells(string cell);
    bool isMarked(State<string>* s);
    double getLinePos(State<string>* s);
    double getColPos(State<string>* s);
    vector<string> tracePath(State<string>* current);
    vector<pair<string, double>> getCostPath();
    void buildCostPath(vector<string> path, Searchable<string> *searchable);
    vector<pair<string, double>>::iterator findCostInPath(string name, double cost);
    int findPrevSumCost(vector<string> path, unordered_map<string, State<string>*> tmpMap, string name);
};


#endif //MILESTONE_2_MATRIXSEARCHER_H