//
// Created by Jonat on 01/11/2024.
//

#ifndef MB_TOG_GROEPJE10_TRANSITIONFUNCTION_H
#define MB_TOG_GROEPJE10_TRANSITIONFUNCTION_H

// Project files
#include "Utils.h"

// Dependencies
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <tuple>
#include "../libs/nlohmann/json.hpp"
#include <fstream>


using json = nlohmann::json;




class TransitionFunction {
private:
    // Transition map that defines the Turing machine's behavior.
    // The key is a pair consisting of:
    //   - currentState: A string representing the current state of the Turing machine.
    //   - readSymbols: A vector of characters representing symbols read from each tape.
    // The value is a tuple consisting of:
    //   - nextState: A string representing the next state after this transition.
    //   - writeSymbols: A vector of characters representing symbols to write on each tape.
    //   - movements: A vector of Direction enums indicating the head movement (LEFT, RIGHT, or STAY) for each tape.
    std::map<std::tuple<std::string, std::vector<char>>,
    std::tuple<std::string, std::vector<char>, std::vector<Direction>>> transitions;

public:

    // Adds a new transition to the transition map for the Turing machine.
    // Parameters:
    // - currentState: The current state from which the transition starts.
    // - readSymbols: A vector of symbols read from each tape in this state.
    // - nextState: The next state to transition to after this operation.
    // - writeSymbols: A vector of symbols to write to each tape during this transition.
    // - movements: A vector of Direction enums indicating head movements for each tape.
    void addTransition(const std::string& currentState, const std::vector<char>& readSymbols,
                       const std::string& nextState, const std::vector<char>& writeSymbols,
                       const std::vector<Direction>& movements);

    // Retrieves a transition for the specified current state and read symbols.
    // Parameters:
    // - currentState: The current state of the Turing machine.
    // - readSymbols: A vector of characters representing the symbols read from each tape.
    // Returns:
    // - A tuple containing:
    //   - nextState: The state to transition to.
    //   - writeSymbols: The symbols to write on each tape.
    //   - movements: The head movements for each tape.
    // Throws:
    // - std::out_of_range if no matching transition is found in the transition map.
    std::tuple<std::string, std::vector<char>, std::vector<Direction>>
    getTransition(const std::string& currentState, const std::vector<char>& readSymbols);

    // Checks if a transition exists for the specified current state and read symbols.
    // Parameters:
    // - currentState: The current state of the Turing machine.
    // - readSymbols: A vector of characters representing the symbols read from each tape.
    // Returns:
    // - true if a transition exists for the given state and symbols; false otherwise.
    bool hasTransition(const std::string& currentState, const std::vector<char>& readSymbols);


};

TransitionFunction parseTransitionFile(const std::string &filename);



#endif //MB_TOG_GROEPJE10_TRANSITIONFUNCTION_H
