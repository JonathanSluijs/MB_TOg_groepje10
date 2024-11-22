//
// Created by Jonat on 01/11/2024.
//

#ifndef MB_TOG_GROEPJE10_TRANSITIONFUNCTION_H
#define MB_TOG_GROEPJE10_TRANSITIONFUNCTION_H

// Project files
#include "Utils.h"

// Dependencies
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <fstream>
#include "../libs/nlohmann/json.hpp"

using json = nlohmann::json;

/**
 * @brief Represents the transition function of a Turing Machine.
 *
 * The transition function defines how the Turing Machine transitions from one state to another based on the current
 * state and the symbols read from the tapes. This class allows adding transitions, checking for transitions, and retrieving
 * the transition for a given state and symbols.
 */
class TransitionFunction {
private:
    // Map that stores transitions using a pair of current state and read symbols as the key
    std::map<std::pair<std::string, std::vector<char>>, std::tuple<std::string, std::vector<char>, std::vector<Direction>>> transitions;

public:
    /**
     * @brief Adds a new transition to the transition function.
     * @param currentState The current state of the Turing Machine.
     * @param readSymbols The symbols read from the tapes.
     * @param nextState The state to transition to.
     * @param writeSymbols The symbols to write on the tapes.
     * @param movements The movements of the tape heads.
     */
    void addTransition(const std::string& currentState, const std::vector<char>& readSymbols,
                       const std::string& nextState, const std::vector<char>& writeSymbols,
                       const std::vector<Direction>& movements);

    /**
     * @brief Gets the transition for the given state and read symbols.
     * @param currentState The current state of the Turing Machine.
     * @param readSymbols The symbols read from the tapes.
     * @return A tuple containing the next state, symbols to write, and head movements.
     */
    std::tuple<std::string, std::vector<char>, std::vector<Direction>> getTransition(const std::string& currentState, const std::vector<char>& readSymbols);

    /**
     * @brief Checks if a transition exists for the given state and read symbols.
     * @param currentState The current state of the Turing Machine.
     * @param readSymbols The symbols read from the tapes.
     * @return True if a transition exists, otherwise false.
     */
    bool hasTransition(const std::string& currentState, const std::vector<char>& readSymbols);
};

/**
     * @brief Parses transitions from a JSON file and adds them to the transition function.
     * @param filename The name of the JSON file containing the transitions.
     */
TransitionFunction parseTransitionFile(const std::string &filename);

#endif //MB_TOG_GROEPJE10_TRANSITIONFUNCTION_H
