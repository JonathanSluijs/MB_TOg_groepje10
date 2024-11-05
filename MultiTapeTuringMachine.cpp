//
// Created by Jonat on 01/11/2024.
//

#include "MultiTapeTuringMachine.h"

MultiTapeTuringMachine::MultiTapeTuringMachine(int tapesCount, const std::string &startState, const std::string &accept,
                                               const std::string &reject)   : numTapes(tapesCount), tapes(tapesCount),
                                               currentState(startState),acceptState(accept), rejectState(reject) {};

void MultiTapeTuringMachine::setTransitionFunction(const TransitionFunction& tf) {
    transitionFunction = tf;
}

bool MultiTapeTuringMachine::run() {
    while (currentState != acceptState && currentState != rejectState) {
        // Read symbols from all tapes
        std::vector<char> readSymbols;
        for (auto& tape : tapes) {
            readSymbols.push_back(tape.read());
        }

        // Check if a valid transition exists for the current state and read symbols
        if (!transitionFunction.hasTransition(currentState, readSymbols)) {
            std::cerr << "No valid transition from state " << currentState
                      << " with symbols: ";
            for (char symbol : readSymbols) {
                std::cerr << symbol << " ";
            }
            std::cerr << "\nMachine rejecting due to missing transition.\n";
            currentState = rejectState;
            break;
        }

        // Get the transition details
        auto [newState, writeSymbols, movements] = transitionFunction.getTransition(currentState, readSymbols);

        // Optional debug output for each transition
        std::cout << "Transitioning from state " << currentState << " to state " << newState << "\n";
        std::cout << "Read symbols: ";
        for (char symbol : readSymbols) {
            std::cout << symbol << " ";
        }
        std::cout << "\nWrite symbols: ";
        for (char symbol : writeSymbols) {
            std::cout << symbol << " ";
        }
        std::cout << "\nMovements: ";
        for (Direction dir : movements) {
            std::cout << (dir == LEFT ? "L" : (dir == RIGHT ? "R" : "S")) << " ";
        }
        std::cout << "\n\n";

        // Update state and apply the transition by writing to tapes and moving heads
        currentState = newState;
        for (int i = 0; i < numTapes; i++) {
            tapes[i].write(writeSymbols[i]);
            tapes[i].move(movements[i]);
        }
    }
    return currentState == acceptState;  // Accept if reached accept state
}



void MultiTapeTuringMachine::printTapes() const {
    for (const auto& tape : tapes) {
        tape.print();
    }
}

Tape& MultiTapeTuringMachine::getTape(int index) {
    if (index >= 0 && index < numTapes) {
        return tapes[index];
    } else {
        throw std::out_of_range("Tape index out of range");
    }
}