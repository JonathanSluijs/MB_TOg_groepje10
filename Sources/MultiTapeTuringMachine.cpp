//
// Created by Jonat on 01/11/2024.
//

#include "../Headers/MultiTapeTuringMachine.h"

MultiTapeTuringMachine::MultiTapeTuringMachine(int tapesCount, const std::string &startState, const std::string &accept,
                                               const std::string &reject) : numTapes(tapesCount), tapes(tapesCount),
                                                                            currentState(startState),
                                                                            acceptState(accept), rejectState(reject) {
};

void MultiTapeTuringMachine::setTransitionFunction(const TransitionFunction &tf) {
    transitionFunction = tf;
}

//manual print
bool print = false;

bool MultiTapeTuringMachine::run() {
    while (currentState != acceptState && currentState != rejectState) {
        if (print) { std::cout << "Current State: " << currentState << std::endl; } //TODO LATER LOGGER INTEGRATIE

        std::vector<char> readSymbols;
        for (auto &tape: tapes) {
            readSymbols.push_back(tape.read());
        }

        if (print) {
            std::cout << "Read Symbols: ";
            for (char symbol: readSymbols) {
                std::cout << symbol << ' ';
            }
            std::cout << std::endl;
        }

        if (!transitionFunction.hasTransition(currentState, readSymbols)) {
            currentState = rejectState; // No valid transition, reject
            if(print) {
                std::cout << "No valid transition. Rejecting..." << std::endl;
            }
            break;
        }

        auto [newState, writeSymbols, movements] = transitionFunction.getTransition(currentState, readSymbols);
        if (print) {
            std::cout << "New State: " << newState << std::endl;
            std::cout << "Write Symbols: ";
            for (char symbol: writeSymbols) {
                std::cout << symbol << ' ';
            }
            std::cout << std::endl;

            std::cout << "Movements: ";
            for (auto move: movements) {
                std::cout << (move == LEFT ? "LEFT" : (move == RIGHT ? "RIGHT" : "STAY")) << ' ';
            }
            std::cout << std::endl;
        }

        currentState = newState;
        for (int i = 0; i < numTapes; i++) {
            tapes[i].write(writeSymbols[i]);
            tapes[i].move(movements[i]);
        }
    }
    if(print) {
        std::cout << "Final State: " << currentState << std::endl;
    }
    return currentState == acceptState; // Accept if reached accept state
}


void MultiTapeTuringMachine::printTapes() const {
    for (const auto &tape: tapes) {
        tape.print();
    }
}

Tape &MultiTapeTuringMachine::getTape(int index) {
    if (index >= 0 && index < numTapes) {
        return tapes[index];
    } else {
        throw std::out_of_range("Tape index out of range");
    }
}
