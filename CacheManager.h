//
// Created by fanny on 17/01/2020.
//

#ifndef MILESTONE_2_CACHEMANAGER_H
#define MILESTONE_2_CACHEMANAGER_H
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <functional>
#include <fstream>

using namespace std;

template<class Problem, class Solution> class CacheManager {
     unordered_map<Problem, Solution> hash_map;
public:
    // searches if the solution has a file
    virtual bool findSolution(Problem p) = 0;
    // creates a file for the problem
    virtual void createProblemFile(Problem obj) = 0;
    // creates a file for the solution
    virtual void insertSolution(Problem key, Solution obj) = 0;
    // returns solutions from file
    virtual Solution get(Problem key) = 0;
    // getter
    virtual unordered_map<Problem, Solution> getHashMap() {
        return this->hash_map;
    }
    virtual void addTohHashMap(Problem key, Solution s) {
        this->hash_map.emplace(make_pair(key, s));
    }
};


#endif //MILESTONE_2_CACHEMANAGER_H
