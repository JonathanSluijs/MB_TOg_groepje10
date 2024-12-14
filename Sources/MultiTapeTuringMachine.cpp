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


    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Wacht kort om I/O af te ronden


    logger.finalizeJson();

    toHTML("../OutputFiles/MTMOutput.json", "../OutputFiles/MTMOutput.html");



    return currentState == acceptState;
}

void MultiTapeTuringMachine::finalizeHtml() {
    std::string inputFileName = "../OutputFiles/MTMOutput.json";
    std::string outputFileName = "../OutputFiles/MTMOutput.html";
    toHTML(inputFileName, outputFileName);
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

void MultiTapeTuringMachine::toHTML(const std::string& inputFileName, const std::string& outputFileName) {
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Cannot open input file: " + inputFileName);
    }

    json inputJson;
    try {
        inputFile >> inputJson;
    } catch (const json::parse_error& e) {
        throw std::runtime_error("JSON parsing error: " + std::string(e.what()));
    }
    inputFile.close();

    // Open the HTML output file
    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Cannot open output file: " + outputFileName);
    }

    // Write HTML header
    outputFile << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<title>Turing Machine Log</title>\n</head>\n<body>\n";

    // Write Initialization phase if it exists
    if (inputJson.contains("Initialization")) {
        outputFile << "<h2>Initialization</h2>\n<ul>\n";
        for (const auto& logEntry : inputJson["Initialization"]) {
            outputFile << "<li>[" << logEntry["level"].get<std::string>() << "] " << logEntry["message"].get<std::string>() << "</li>\n";
        }
        outputFile << "</ul>\n";
    }

    // Process numbered phases in order
    int phaseIndex = 0;
    while (inputJson.contains(std::to_string(phaseIndex))) {
        const std::string phaseKey = std::to_string(phaseIndex);
        outputFile << "<h2>" << "Phase: " << phaseKey << "</h2>\n<ul>\n";

        for (const auto& logEntry : inputJson[phaseKey]) {
            outputFile << "<li>[" << logEntry["level"].get<std::string>() << "] " << logEntry["message"].get<std::string>() << "</li>\n";
        }
        outputFile << "</ul>\n";
        phaseIndex++;
    }

    // Write Finalization phase if it exists
    if (inputJson.contains("Finalization")) {
        outputFile << "<h2>Finalization</h2>\n<ul>\n";
        for (const auto& logEntry : inputJson["Finalization"]) {
            outputFile << "<li>[" << logEntry["level"].get<std::string>() << "] " << logEntry["message"].get<std::string>() << "</li>\n";
        }
        outputFile << "</ul>\n";
    }

    // Write HTML footer
    outputFile << "</body>\n</html>\n";
    outputFile.close();
}

