//
// Created by Jonat on 01/11/2024.
//

#include "../Headers/TransitionFunction.h"
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

TransitionFunction parseTransitionFile(const std::string &filename) {
    // Open het JSON-bestand
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Kan het bestand niet openen: " + filename);
    }

    // JSON data inlezen
    json j;
    file >> j;

    // Maak een enkele TransitionFunction aan om alle overgangen in op te slaan
    TransitionFunction tf;

    // Parseer elke overgang in het JSON-bestand
    for (const auto& t : j["transitions"]) {
        // Huidige staat
        std::string currentState = t["currentState"];

        // Ingelezen symbolen
        std::vector<char> readSymbols;
        for (const auto& symbol : t["inputSymbols"]) {
            std::string symStr = symbol.get<std::string>();
            if (!symStr.empty()) {
                readSymbols.push_back(symStr[0]); // Eerste karakter van de string
            } else {
                throw std::runtime_error("Leeg symbool gevonden in 'inputSymbols' in JSON-bestand");
            }
        }

        // Volgende staat
        std::string nextState = t["nextState"];

        // Te schrijven symbolen
        std::vector<char> writeSymbols;
        for (const auto& symbol : t["writeSymbols"]) {
            std::string symStr = symbol.get<std::string>();
            if (!symStr.empty()) {
                writeSymbols.push_back(symStr[0]); // Eerste karakter van de string
            } else {
                throw std::runtime_error("Leeg symbool gevonden in 'writeSymbols' in JSON-bestand");
            }
        }

        // Bewegingen
        std::vector<Direction> movements;
        for (const auto& dir : t["directions"]) {
            if (dir == "LEFT") {
                movements.push_back(Direction::LEFT);
            } else if (dir == "RIGHT") {
                movements.push_back(Direction::RIGHT);
            } else if (dir == "STAY") {
                movements.push_back(Direction::STAY);
            } else {
                throw std::runtime_error("Ongeldige richting in JSON: " + dir.get<std::string>());
            }
        }

        // Voeg de overgang toe aan de TransitionFunction
        tf.addTransition(currentState, readSymbols, nextState, writeSymbols, movements);
    }

    // Geef het TransitionFunction object terug met alle overgangen
    return tf;
}
