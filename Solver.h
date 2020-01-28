//
// Created by noa on 17/01/2020.
//

#ifndef MILESTONE_2_SOLVER_H
#define MILESTONE_2_SOLVER_H
template <class Problem, class Solution> class Solver{
public:
    virtual Solution solve(Problem p) = 0;
};


#endif //MILESTONE_2_SOLVER_H
