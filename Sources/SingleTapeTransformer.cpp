#include "../Headers/SingleTapeTransformer.h"


SingleTapeTransformer::SingleTapeTransformer(const std::vector<Tape>& tapes, const std::string& startState, const std::string& acceptState, const std::string& rejectState)
    : tapes(tapes), currentState(startState), acceptState(acceptState), rejectState(rejectState) {}

void SingleTapeTransformer::setTransitionFunction(const TransitionFunction& tf) {
    transitionFunction = tf;
}

bool SingleTapeTransformer::run() {
    Logger logger("../OutputFiles/SingleTapeOutput.txt", "../OutputFiles/SingleTapeOutput.json", false);
    logger.setPhase("Initialization");
    logger.log(Logger::INFO, "Starting Single Tape Transformer...");

    int counter = 0;

    while (currentState != acceptState && currentState != rejectState) {
        logger.setPhase(std::to_string(counter));
        logger.log(Logger::DEBUG, "Current State: " + currentState);

        std::vector<char> readSymbols;
        for (auto& tape : tapes) {
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
        for (int i = 0; i < tapes.size(); i++) {
            tapes[i].write(writeSymbols[i]);
            tapes[i].move(movements[i]);
        }

        counter++;
    }

    logger.setPhase("Finalization");
    logger.log(Logger::INFO, "Final State: " + currentState);

    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Pause briefly for I/O completion

    logger.finalizeJson();

    return currentState == acceptState;
}

std::vector<std::vector<char>> SingleTapeTransformer::to2DArray() {
    std::vector<std::vector<char>> result;

    for (size_t i = 0; i < tapes.size(); ++i) {
        std::string content = tapes[i].getContent();
        std::vector<char> contentRow(content.begin(), content.end());
        result.push_back(contentRow);

        std::vector<char> headMarker(contentRow.size(), ' ');
        int headPos = tapes[i].getHeadPosition();
        if (headPos >= 0 && headPos < static_cast<int>(headMarker.size())) {
            headMarker[headPos] = '^';
        }
        result.push_back(headMarker);
    }

    return result;
}

void SingleTapeTransformer::print2DArray() {
    auto array = to2DArray();
    for (const auto& row : array) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}
