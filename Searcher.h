//
// Created by noa on 18/01/2020.
//

#ifndef MILESTONE_2_SEARCHER_H
#define MILESTONE_2_SEARCHER_H


#include "Searchable.h"
template <class T, class Solution> class Searcher {
public:
    virtual Solution search(Searchable<T>* searchable) = 0;
};


#endif //MILESTONE_2_SEARCHER_H
