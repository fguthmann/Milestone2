//
// Created by noa on 17/01/2020.
//

#include <algorithm>
#include "StringReverser.h"
// reverses given string
string StringReverser::solve(string p) {
   // string answer = vectorToString(p);
    reverse(p.begin(), p.end());
    return p;
}
string StringReverser::vectorToString(vector<string> matrix) {
    string s = "";
    vector<string>::iterator it;
    for (it = matrix.begin(); it != matrix.end(); ++it) {
        s += (*it);
        //s += "\n";
    }
    return s;
}