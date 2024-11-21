//
// Created by cainh on 25/09/2024.
//

#include "../Headers/CFG.h"
#include "../libs/nlohmann/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

CFG::CFG(const std::string &filename) {
    std::ifstream input(filename);

    json j;
    input >> j;

    for (const auto &variable: j["Variables"]) {
        variables.push_back(variable);
    }
    std::sort(variables.begin(), variables.end());

    for (const auto &terminal: j["Terminals"]) {
        terminals.push_back(terminal);
    }
    std::sort(terminals.begin(), terminals.end());

    for (const auto &production: j["Productions"]) {
        if (production["body"].empty()) {
            productions[production["head"]].push_back({"`"});
        } else {
            productions[production["head"]].push_back(production["body"]);
        }
    }
    this->sortProductions();

    start = j["Start"];
}

void CFG::print() const {
    std::cout << "V = {";
    for (int i = 0; i < variables.size(); i++) {
        std::cout << variables[i];
        if (i != variables.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;

    std::cout << "T = {";
    for (int i = 0; i < terminals.size(); i++) {
        std::cout << terminals[i];
        if (i != terminals.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;

    std::cout << "P = {" << std::endl;
    for (const auto &production: productions) {
        for (const auto &body: production.second) {
            std::cout << "    " << production.first << " -> `";
            if (!(body.size() == 1 && body[0] == "`")) {
                for (int i = 0; i < body.size(); i++) {
                    std::cout << body[i];
                    if (i != body.size() - 1) {
                        std::cout << " ";
                    }
                }
            }
            std::cout << "`" << std::endl;
        }
    }
    std::cout << "}" << std::endl;

    std::cout << "S = " << start << std::endl;
}


void CFG::sortProductions() {
    for (auto &production: productions) {
        // Sort the outer vector using lexicographical comparison of inner vectors
        sort(production.second.begin(), production.second.end(),
             [this](const std::vector<std::string> &prod1, const std::vector<std::string> &prod2) {
                 return this->compareProductions(prod1, prod2);
             });
    }
}

bool CFG::compareProductions(const std::vector<std::string> &prod1, const std::vector<std::string> &prod2) {
    // Compare lexicographically
    for (size_t i = 0; i < std::min(prod1.size(), prod2.size()); ++i) {
        if (prod1[i] != prod2[i]) {
            return prod1[i] < prod2[i];  // Lexicographical order
        }
    }
    // If all compared elements are the same, the longer production comes first
    return prod1.size() > prod2.size();  // Longer production comes first
}

bool CFG::isTerminal(const std::string &str) const {
    return std::find(terminals.begin(), terminals.end(), str) != terminals.end();
}

bool CFG::isVariable(const std::string &str) const {
    return std::find(variables.begin(), variables.end(), str) != variables.end();
}


std::vector<std::string> CFG::getVariables() const {
    return variables;
}

std::vector<std::string> CFG::getTerminals() const {
    return terminals;
}

std::map<std::string, std::vector<std::vector<std::string>>> CFG::getProductions() const {
    return productions;
}

const std::string& CFG::getStartSymbol() const {
    return start;
}
