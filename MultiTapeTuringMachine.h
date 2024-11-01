//
// Created by Jonat on 01/11/2024.
//

#ifndef MB_TOG_GROEPJE10_MULTITAPETURINGMACHINE_H
#define MB_TOG_GROEPJE10_MULTITAPETURINGMACHINE_H

// Project files
#include "Tape.h"
#include "TransitionFunction.h"

// Dependencies
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <tuple>


class MultiTapeTuringMachine {
private:
    int numTapes;
    std::vector<Tape> tapes;
    std::string currentState;
    std::string acceptState;
    std::string rejectState;
    TransitionFunction transitionFunction;

public:
    // Constructor
    MultiTapeTuringMachine(int tapesCount, const std::string& startState,const std::string& accept, const std::string& reject);

    void setTransitionFunction(const TransitionFunction& tf);

    bool run();

    void printTapes() const;

    Tape& getTape(int index);


};


#endif //MB_TOG_GROEPJE10_MULTITAPETURINGMACHINE_H
