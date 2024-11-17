//
// Created by 2005e on 25/10/2024.
//

#include "../Headers/Logger.h"
#include "../Headers/CFG.h"


std::string Logger::setToString(const StringSet &string_set) {
    std::string output = "{";
    for (auto it = string_set.begin(); it != string_set.end(); it++) {
        if (it != string_set.begin())
            output.append(", ");
        if (*it == " ")
            output.append("");
        else
            output.append(*it);
    }
    output.append("}");
    return output;
}

std::vector<std::string> Logger::splitString(const std::string &str) {
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string token;

    while (iss >> token) {
        if (token == " ") {
            result.emplace_back("");
        } else {
            token.erase(std::remove(token.begin(), token.end(), '`'), token.end());
            result.push_back(token);
        }
    }
    if (result.empty())
        result.emplace_back("");
    return result;
}

std::string Logger::generateSpaces(int count, bool underlining) {
    std::string spaces;
    if (underlining)
        for (int i = 0; i < count; ++i)
            spaces += "-";
    else
        for (int i = 0; i < count; ++i)
            spaces += " ";
    return std::move(spaces);
}

void Logger::printAcceptanceTable(const std::vector<std::vector<TableObject>> &table) {
    std::vector<int> table_sizes;
    table_sizes.reserve(table.size());

    for (int j = 0; j < table.size(); ++j) {
        int max_setsize = 0;
        for (int i = table.size() - 1 - j; i >= 0; --i) {
            int set_size = setToString(table[i][j].getVariables()).size();
            if (set_size > max_setsize) {
                max_setsize = set_size;
            }
        }
        table_sizes.push_back(max_setsize);
    }
    for (int i = table.size() - 1; i >= 0; --i) {
        std::cout << "|";
        for (int j = 0; j < table.size() - i; ++j) {
            std::string set = setToString(table[i][j].getVariables());
            int extra_spaces = table_sizes[j] - set.size();

            std::string spaces;
            for (int counter = 0; counter < extra_spaces; ++counter) {
                spaces += " ";
            }
            std::cout << " " + setToString(table[i][j].getVariables()) + spaces + "  |";
        }
        std::cout << "\n";
    }
}

void Logger::printProductions(const std::map<std::string, StringSet> &productions) {
    std::cout << "P = {" << std::endl;
    std::string align_space = "    ";
    for (const auto &body: productions) {
        for (auto it = body.second.begin(); it != body.second.end(); ++it) {
            std::cout << align_space << body.first << " -> `" << *it << "`" << std::endl;
        }
    }
    std::cout << "}" << std::endl;
}
