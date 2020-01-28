//
// Created by noa on 18/01/2020.
//

#ifndef MILESTONE_2_STATE_H
#define MILESTONE_2_STATE_H

#include <string>
using namespace std;
template <class T> class State {
    T state;
    double cost;
    State<T>* cameFrom;
public:
    // constructor
    State (T s, double c, State<T>* cf) {
        this->state = s;
        this->cost = c;
        this->cameFrom = cf;
    }
    // override of equals
    bool Equals(State<T> s) {
        return this->state == s.state;
    }
    // getters
    T getState() {
        return this->state;
    }
    double getCost() {
        return this->cost;
    }
    State<T>* getFather() {
        return this->cameFrom;
    }
    // setter
    void setFather(State<T> s) {
        State<T>* sFather = s.getFather();
        this->cameFrom = new State(s.state, s.cost, sFather);
    }
    // destructor
    /*~State() {
        while (this->cameFrom != NULL) {
            delete(this->cameFrom);
        }
    }*/
};

#endif //MILESTONE_2_STATE_H