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


    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Wacht kort om I/O af te ronden (Anders had ik bugs)


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

    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Cannot open output file: " + outputFileName);
    }


    outputFile << R"(<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Turing Machine Log</title>
<style>
    body {
        font-family: Arial, sans-serif;
        line-height: 1.6;
        margin: 0;
        padding: 0;
        background-color: #f4f4f9;
        color: #333;
    }
    h2 {
        color: #444;
        background-color: #e7e7e7;
        padding: 10px;
        border-left: 4px solid #4CAF50;
    }
    ul {
        list-style-type: none;
        padding: 0;
    }
    li {
        margin: 5px 0;
        padding: 10px;
        background: #fff;
        border: 1px solid #ddd;
        border-radius: 4px;
    }
    table {
        width: 100%;
        border-collapse: collapse;
        margin: 10px 0;
        table-layout: fixed; /* Zorg ervoor dat kolommen gelijk verdeeld worden */
    }
    table, th, td {
        border: 1px solid #ddd;
    }
    th, td {
        text-align: center;
        padding: 8px;
    }
    th {
        background-color: #4CAF50;
        color: white;
        width: 200px; /* Standaard breedte instellen voor kolommen */
    }
</style>
</head>
<body>
)";


    if (inputJson.contains("Initialization")) {
        outputFile << "<h2>Initialization</h2>\n<ul>\n";
        for (const auto& logEntry : inputJson["Initialization"]) {
            outputFile << "<li>[" << logEntry["level"].get<std::string>() << "] "
                       << logEntry["message"].get<std::string>() << "</li>\n";
        }
        outputFile << "</ul>\n";
    }


    int phaseIndex = 0;
    while (inputJson.contains(std::to_string(phaseIndex))) {
        const std::string phaseKey = std::to_string(phaseIndex);
        outputFile << "<h2>Phase: " << phaseKey << "</h2>\n<ul>\n";

        int tapeIndex = 0;
        for (const auto& logEntry : inputJson[phaseKey]) {
            std::string level = logEntry["level"].get<std::string>();
            std::string message = logEntry["message"].get<std::string>();

            if (level == "RUN" && message.find("Tape Content") != std::string::npos) {
                std::string tapeContent = message.substr(message.find(":") + 2);
                outputFile << "<table>\n<tr><th>Tape " << std::to_string(tapeIndex) << "</th>";
                for (char ch : tapeContent) {
                    outputFile << "<td>" << ch << "</td>";
                }
                outputFile << "</tr>\n</table>\n";
            } else {
                outputFile << "<li>[" << level << "] " << message << "</li>\n";
            }
            tapeIndex++;
        }
        outputFile << "</ul>\n";
        phaseIndex++;
    }


    if (inputJson.contains("Finalization")) {
        outputFile << "<h2>Finalization</h2>\n<ul>\n";
        for (const auto& logEntry : inputJson["Finalization"]) {
            outputFile << "<li>[" << logEntry["level"].get<std::string>() << "] "
                       << logEntry["message"].get<std::string>() << "</li>\n";
        }
        outputFile << "</ul>\n";
    }


    outputFile << "</body>\n</html>\n";
    outputFile.close();
}
