#include "../Headers/MultiTapeTuringMachine.h"

MultiTapeTuringMachine::MultiTapeTuringMachine(int tapesCount, const std::string &startState, const std::string &accept,
                                               const std::string &reject) : numTapes(tapesCount), tapes(tapesCount),
                                                                            startState(startState),
                                                                            currentState(startState),
                                                                            acceptState(accept), rejectState(reject) {
};

void MultiTapeTuringMachine::setTransitionFunction(const TransitionFunction &tf) {
    transitionFunction = tf;
}

bool MultiTapeTuringMachine::run() {
    Logger logger("../OutputFiles/MTMOutput.txt", "../OutputFiles/MTMOutput.json", true);
    logger.setPhase("Initialization");
    logger.log(Logger::INFO, "Starting Turing Machine...");

    int counter = 0;

    while (currentState != acceptState && currentState != rejectState) {
        logger.setPhase(std::to_string(counter));
        logger.log(Logger::DEBUG, "Current State: " + currentState);

        std::vector<char> readSymbols;
        for (auto &tape : tapes) {
            readSymbols.push_back(tape.read());
            logger.log(Logger::RUN, "Tape Content: " + tape.getContent());
        }

        logger.log(Logger::DEBUG, "Read Symbols: " + std::string(readSymbols.begin(), readSymbols.end()));

        if (!transitionFunction.hasTransition(currentState, readSymbols)) {
            logger.setPhase("Error Handling");
            logger.log(Logger::WARN, "No valid transition found. Rejecting input.");
            currentState = rejectState;
            break;
        }

        auto [newState, writeSymbols, movements] = transitionFunction.getTransition(currentState, readSymbols);
        logger.log(Logger::DEBUG, "Transition to state: " + newState);

        currentState = newState;
        for (int i = 0; i < numTapes; i++) {
            tapes[i].write(writeSymbols[i]);
            tapes[i].move(movements[i]);
        }

        counter++;
    }

    logger.setPhase("Finalization");
    logger.log(Logger::INFO, "Final State: " + currentState);

    return currentState == acceptState;
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

void MultiTapeTuringMachine::reset() {
    currentState = startState;
    for (auto &tape: tapes) {
        tape.setContent("_");
    }
}
