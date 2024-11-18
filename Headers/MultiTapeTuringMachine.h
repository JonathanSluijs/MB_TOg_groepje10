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
    // Constructor for the MultiTapeTuringMachine class
    // Initializes the machine with the specified number of tapes and states
    // Parameters:
    // - tapesCount: The number of tapes for this Turing machine
    // - startState: The initial state of the machine
    // - accept: The accept state of the machine
    // - reject: The reject state of the machine
    MultiTapeTuringMachine(int tapesCount, const std::string& startState,const std::string& accept, const std::string& reject);


    // Sets the transition function for the Turing machine
    // Parameters:
    // - tf: A TransitionFunction object containing the transition rules for this machine
    void setTransitionFunction(const TransitionFunction& tf);

    // Executes the Turing machine from the current state until it reaches an accept or reject state
    // Returns:
    // - true if the machine reaches the accept state
    // - false if the machine reaches the reject state or has no valid transition
    bool run();

    // Prints the contents of all tapes and their head positions
    // Used for debugging
    void printTapes() const;

    // Retrieves a reference to the specified tape in the machine
    // Parameters:
    // - index: The index of the tape to retrieve
    // Returns:
    // - A reference to the requested Tape object
    // Throws:
    // - std::out_of_range if the index is not within the valid range
    Tape& getTape(int index);

    //TODO: Add function copy from tape to tape
    void copyTapeSymbol(int from, int to);
};


#endif //MB_TOG_GROEPJE10_MULTITAPETURINGMACHINE_H
