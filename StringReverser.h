//
// Created by noa on 17/01/2020.
//

#ifndef MILESTONE_2_STRINGREVERSER_H
#define MILESTONE_2_STRINGREVERSER_H

#include <string>
#include "Solver.h"
#include "Searcher.h"

using namespace std;

class StringReverser : public Solver<string, string> {
    Searcher<string, string> *searcher;
public:
    virtual string solve(string p);
    string vectorToString(vector<string> p);
};


#endif //MILESTONE_2_STRINGREVERSER_H
