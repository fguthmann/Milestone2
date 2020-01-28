//
// Created by noa on 18/01/2020.
//

#include "Matrix.h"
// constructor
Matrix::Matrix(vector<string> matrix, string start, string end) {
    this->numOfLines = 0;
    int col = 0;
    auto it = matrix.begin();
    int i = 0;
    while (it != matrix.end()) {
        i++;
        string l = *it;
        while (!l.empty()) {
            string cost;
            size_t comma = l.find(",");
            if (comma == string::npos) {
                cost = removeSpaces(l);
            } else {
                cost = removeSpaces(l.substr(0, comma));
            }
            // add point to map
            string pos = to_string(this->numOfLines);
            pos += ",";
            pos += to_string(col);
            State<string> *s = new State<string>(pos, stod(cost), NULL);
            this->addToMap(pos, s);
            if (!start.compare(pos)) {
                // end point
                this->entry = s;
            }
            if (!end.compare(pos)) {
                // end point
                this->exit = s;
            }
            col++;
            if (comma == string::npos) {
                l.clear();
            } else {
                l = l.substr(comma+1);
            }
        }
        if (this->numOfLines == 0) {
            // record number of columns
            this->numOfCols = col;
        }
        // end of line
        this->numOfLines++;
        col = 0;
        it++;
    }
}

// removes excess spaces and tabs in lines extracted from text file
string Matrix::removeSpaces(string str) {
    string newStr;
    for (char i : str) {
        if ((i != ' ') && (i != '\t') && (i != '\n') && (i != '\r')) {
            newStr.push_back(i);
        }
    }
    return newStr;
}

State<string>* Matrix::getInitialState() {
    return this->entry;
}

State<string>* Matrix::getGoalState() {
    return this->exit;
}

bool Matrix::isGoalState(State<string>* obj) {
    return this->exit->Equals(*obj);
}
// gets all neighbours of vertex in matrix
vector<State<string>*> Matrix::getAllPossibleStates(State<string>* obj) {
    unordered_map<string, State<string>*> tmpMap = this->getMap();
    vector<State<string>*> adjacents;
    string pos = obj->getState();
    auto divide = pos.find(",");
    string linePos = pos.substr(0, divide);
    string colPos = pos.substr(divide+1);
    // find and add adjacents to list
    string place1 = linePos;
    string place2 = linePos;
    string place3 = to_string(stoi(linePos)+1);
    string place4 = to_string(stoi(linePos)-1);
    if ((stoi(place3) >= 0) && (stoi(place3) < this->numOfLines)) {
        place3 += ",";
        place3 += colPos;
        adjacents.push_back(tmpMap.find(place3)->second);
    }
    if ((stoi(place4) >= 0) && (stoi(place4) < this->numOfLines)) {
        place4 += ",";
        place4 += colPos;
        adjacents.push_back(tmpMap.find(place4)->second);
    }
    int colPlace1 = stoi(colPos)+1;
    int colPlace2 = stoi(colPos)-1;
    if ((colPlace1 >= 0) && (colPlace1 < this->numOfCols)) {
        place1 += ",";
        place1 += to_string(colPlace1);
        adjacents.push_back(tmpMap.find(place1)->second);
    }
    if ((colPlace2 >= 0) && (colPlace2 < this->numOfCols)) {
        place2 += ",";
        place2 += to_string(colPlace2);
        adjacents.push_back(tmpMap.find(place2)->second);
    }
    return adjacents;
}
// destructor
Matrix::~Matrix() {
    if (this->entry != nullptr) {
        delete(this->entry);
    }
    if (this->exit != nullptr) {
        delete(this->exit);
    }
    while (!this->getMap().empty()) {
        auto s = this->getMap().erase(this->getMap().begin());
        delete(s->second);
    }
    delete(this);
}