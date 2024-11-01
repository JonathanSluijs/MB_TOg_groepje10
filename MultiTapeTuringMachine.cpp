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
        std::vector<char> readSymbols;
        for (auto& tape : tapes) {
            readSymbols.push_back(tape.read());
        }

        if (!transitionFunction.hasTransition(currentState, readSymbols)) {
            currentState = rejectState;  // No valid transition, reject
            break;
        }

        auto [newState, writeSymbols, movements] = transitionFunction.getTransition(currentState, readSymbols);

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