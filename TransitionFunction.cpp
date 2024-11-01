//
// Created by Jonat on 01/11/2024.
//

#include "TransitionFunction.h"
void TransitionFunction::addTransition(const std::string& currentState, const std::vector<char>& readSymbols,
                   const std::string& nextState, const std::vector<char>& writeSymbols,
                   const std::vector<Direction>& movements) {
    transitions[{currentState, readSymbols}] = {nextState, writeSymbols, movements};
}

std::tuple<std::string, std::vector<char>, std::vector<Direction>>
TransitionFunction::getTransition(const std::string& currentState, const std::vector<char>& readSymbols) {
    return transitions[{currentState, readSymbols}];
}

bool TransitionFunction::hasTransition(const std::string& currentState, const std::vector<char>& readSymbols) {
    return transitions.find({currentState, readSymbols}) != transitions.end();
}
