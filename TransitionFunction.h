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

class TransitionFunction {
private:
    // Maps (current state, symbols read from each tape) to (next state, symbols to write, head movements)
    std::map<std::tuple<std::string, std::vector<char>>,
    std::tuple<std::string, std::vector<char>, std::vector<Direction>>> transitions;

public:

    // Add to transitions
    void addTransition(const std::string& currentState, const std::vector<char>& readSymbols,
                       const std::string& nextState, const std::vector<char>& writeSymbols,
                       const std::vector<Direction>& movements);

    // Get transition
    std::tuple<std::string, std::vector<char>, std::vector<Direction>>
    getTransition(const std::string& currentState, const std::vector<char>& readSymbols);


    bool hasTransition(const std::string& currentState, const std::vector<char>& readSymbols);

};


#endif //MB_TOG_GROEPJE10_TRANSITIONFUNCTION_H
