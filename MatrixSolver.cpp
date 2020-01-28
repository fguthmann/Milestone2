//
// Created by noa on 19/01/2020.
//

#include "MatrixSolver.h"
MatrixSolver::MatrixSolver() {
    this->searcher = new AstarAlgorithm();
}

string MatrixSolver::solve(vector<string> p) {
    // extract matrix and points from vector
    string solution;
    auto it = prev(p.end());
    string end = *it;
    it = prev(it);
    string start = *it;
    p.erase(it, p.end());
    this->searchable = new Matrix(p, start, end);
    vector<pair<string, double>> solutionMap = this->searcher->search(this->searchable);
    auto pos = solutionMap.begin();
    pos++;
    for (pos; pos != solutionMap.end(); ++pos) {
        string direction = findDirection(pos->first);
        solution += (direction + " (" + to_string((int)pos->second) + "), ");
    }
    return solution;
}

string MatrixSolver::findDirection(string current) {
    State<string>* father = this->searchable->getMap().find(current)->second->getFather();
    int currentLine = this->searcher->getLinePos(this->searchable->getMap().find(current)->second);
    int currentCol = this->searcher->getColPos(this->searchable->getMap().find(current)->second);
    int fatherLine = this->searcher->getLinePos(father);
    int fatherCol = this->searcher->getColPos(father);

    // if the current vertex and it's father in the same column
    if (currentCol == fatherCol) {
        if (currentLine > fatherLine) {
            return "DOWN";
        } else {
            return "UP";
        }
    }

        // if the current vertex and it's father in the same line
    else if (currentLine == fatherLine) {
        if (currentCol > fatherCol) {
            return "RIGHT";
        } else {
            return "LEFT";
        }
    }
}