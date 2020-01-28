//
// Created by fanny on 18/01/2020.
//

#ifndef MILESTONE_2_FILECACHEMANAGER_H
#define MILESTONE_2_FILECACHEMANAGER_H

#include "CacheManager.h"

class FileCacheManager : public CacheManager<string, string> {
    hash<string> hasher;
public:
    FileCacheManager();
    virtual bool findSolution(string p);
    virtual void createProblemFile(string obj);
    virtual void insertSolution(string key, string obj);
    string get(string key);
};


#endif //MILESTONE_2_FILECACHEMANAGER_H

