#include "../Headers/SingleTapeTransformer.h"


SingleTapeTransformer::SingleTapeTransformer(const std::vector<Tape>& tapes, const std::string& startState, const std::string& acceptState, const std::string& rejectState)
    : tapes(tapes), currentState(startState), acceptState(acceptState), rejectState(rejectState) {
    // Initialize headPointerTapes with blank tapes
    for (const auto& tape : tapes) {
        Tape headPointerTape; // Use default constructor
        // Fill the headPointerTape with spaces to match the original tape's length
        for (size_t j = 0; j < tape.getContent().size(); ++j) {
            headPointerTape.write(' ');
            if (j < tape.getContent().size() - 1) {
                headPointerTape.move(RIGHT);
            }
        }
        // Reset head to the start and write the initial head marker
        while (headPointerTape.getHeadPosition() > 0) {
            headPointerTape.move(LEFT);
        }
        headPointerTape.write('^');
        headPointerTapes.push_back(headPointerTape);
    }
}

void SingleTapeTransformer::setTransitionFunction(const TransitionFunction& tf) {
    transitionFunction = tf;
}

void SingleTapeTransformer::mergeTransitionsToSimulateSingleTape() {
    Logger logger("../OutputFiles/MergedTransitionsOutput.txt", "../OutputFiles/MergedTransitionsOutput.json", false);
    logger.setPhase("Merge Transitions");
    logger.log(Logger::INFO, "Starting to merge transitions to simulate single tape...");

    // Encode the single tape using '#' delimiters for separating tapes
    std::string singleTape;
    std::vector<int> headPositions;
    for (size_t i = 0; i < tapes.size(); ++i) {
        singleTape += tapes[i].getContent();
        headPositions.push_back(tapes[i].getHeadPosition() + singleTape.size() - tapes[i].getContent().size());
        if (i < tapes.size() - 1) {
            singleTape += "#";
        }
    }

    logger.log(Logger::DEBUG, "Encoded single tape: " + singleTape);

    // Merge transitions for all tapes into a single-tape representation
    for (const auto& transition : transitionFunction.getAllTransitions()) {
        const auto& key = transition.first; // {currentState, readSymbols}
        const auto& value = transition.second; // {nextState, writeSymbols, movements}

        const auto& [currentState, readSymbols] = key;
        const auto& [nextState, writeSymbols, movements] = value;

        std::string mergedReadSymbols;
        std::string mergedWriteSymbols;

        // Building merged symbols
        for (size_t i = 0; i < tapes.size(); ++i) {
            mergedReadSymbols += readSymbols[i];
            mergedWriteSymbols += writeSymbols[i];
            if (i < tapes.size() - 1) {
                mergedReadSymbols += "#";
                mergedWriteSymbols += "#";
            }
        }

        // Movements for the single tape
        std::vector<Direction> mergedMovements(singleTape.size(), Direction::STAY);
        size_t tapeIndex = 0;
        for (size_t i = 0; i < movements.size(); ++i) {
            while (tapeIndex < singleTape.size() && singleTape[tapeIndex] != '#') {
                ++tapeIndex;
            }
            if (movements[i] == Direction::LEFT) {
                if (tapeIndex > 0) mergedMovements[tapeIndex - 1] = Direction::LEFT;
            } else if (movements[i] == Direction::RIGHT) {
                if (tapeIndex < singleTape.size() - 1) mergedMovements[tapeIndex + 1] = Direction::RIGHT;
            }
        }

        // Add the merged transition to the single tape transition function

        transitionFunction.addTransition(
            currentState,
            std::vector<char>(mergedReadSymbols.begin(), mergedReadSymbols.end()),
            nextState,
            std::vector<char>(mergedWriteSymbols.begin(), mergedWriteSymbols.end()),
            mergedMovements
        );

        logger.log(Logger::DEBUG, "Added merged transition: \"" + currentState + "\" -> \"" + nextState + "\" with read symbols [" + mergedReadSymbols + "] and write symbols [" + mergedWriteSymbols + "].");
    }

    logger.setPhase("Finalization");
    logger.log(Logger::INFO, "Transitions successfully merged.");
}

bool SingleTapeTransformer::run() {
    Logger logger("../OutputFiles/SingleTapeOutput.txt", "../OutputFiles/SingleTapeOutput.json", false);
    logger.setPhase("Initialization");
    logger.log(Logger::INFO, "Starting Single Tape Transformer...");

    mergeTransitionsToSimulateSingleTape(); // Merge them before running

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

            // Update head pointer tape
            int currentHead = headPointerTapes[i].getHeadPosition();
            headPointerTapes[i].write(' '); // Clear previous head position marker
            headPointerTapes[i].move(movements[i]);
            headPointerTapes[i].write('^'); // Mark new head position
        }

        counter++;
    }

    logger.setPhase("Finalization");
    logger.log(Logger::INFO, "Final State: " + currentState);

    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Pause briefly for I/O completion (clion AI recommend)

    logger.finalizeJson();

    return currentState == acceptState;
}

std::vector<std::string> SingleTapeTransformer::toSingleTape() {
    std::string contentRow;  // Combined content of all tapes
    std::string headPointerRow;  // Combined head pointers

    for (size_t i = 0; i < tapes.size(); ++i) {
        std::string content = tapes[i].getContent();
        int headPos = tapes[i].getHeadPosition();

        // Append tape content to the contentRow
        contentRow += content;

        // Append head pointer markers to the headPointerRow
        for (size_t j = 0; j < content.size(); ++j) {
            headPointerRow += (j == static_cast<size_t>(headPos)) ? '^' : ' ';
        }

        // Add separator between tapes, except for the last one
        if (i < tapes.size() - 1) {
            contentRow += '#';
            headPointerRow += ' ';
        }
    }

    return {contentRow, headPointerRow};
}

void SingleTapeTransformer::printSingleTape() {
    auto singleTape = toSingleTape();

    // Print the combined content row
    std::cout << singleTape[0] << std::endl;

    // Print the combined head pointer row
    std::cout << singleTape[1] << std::endl;
}

