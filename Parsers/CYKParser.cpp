//
// Created by emir on 11/17/24.
//

#include "CYKParser.h"
#include "../Headers/CFG.h"
#include <algorithm>
#include <set>
#include <stdexcept>

parser::CYKParser &parser::CYKParser::getInstance() {
    static CYKParser _instance;
    return _instance;
}

bool parser::CYKParser::parse(const std::string &input, const CFG &cfg) {
    if (input.empty()) {
        throw std::invalid_argument("Input string is empty");
    }


    std::vector<std::vector<std::set<std::string> > > table(input.size());
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input.size() - i; j++) {
            table[i].push_back({{}});
        }
    }

    // First row
    for (int i = 0; i < input.size(); i++) {
        for (const auto &production: cfg.getProductions()) {
            for (const auto &body: production.second) {
                if (body.size() == 1 && body[0] == input.substr(i, 1)) {
                    if (*table[i][0].begin() == "") {
                        table[i][0] = {production.first};
                    } else {
                        table[i][0].insert(production.first);
                    }
                }
            }
        }
    }

    // Rest of the table
    int row = 1;
    while (row < input.size()) {
        for (int i = 1; i <= table.size() - row; i++) {
            int j = row + i;
            for (const auto &production: cfg.getProductions()) {
                for (const auto &body: production.second) {
                    bool added = false;
                    if (body.size() < 2) {
                        continue;
                    }
                    for (int k = i; k < j; k++) {
                        if (std::find(table[i - 1][k - i].begin(), table[i - 1][k - i].end(), body[0]) !=
                            table[i - 1][k - i].end() &&
                            std::find(table[k][j - k - 1].begin(), table[k][j - k - 1].end(), body[1]) !=
                            table[k][j - k - 1].end()) {
                            if (*table[i - 1][j - i].begin() == "") {
                                table[i - 1][j - i] = {production.first};
                            } else {
                                table[i - 1][j - i].insert(production.first);
                            }
                            added = true;
                            break;
                        }
                    }
                    if (added) {
                        break;
                    }
                }
            }
        }
        row++;
    }

    std::vector<int> columnWidths;
    for (int i = 0; i < input.size(); i++) {
        int width = 0;
        for (int j = 0; j < input.size() - i; j++) {
            if (table[i][j].size() > width) {
                width = table[i][j].size();
            }
        }
        columnWidths.push_back(width);
    }
    return std::find(table[0][input.size() - 1].begin(), table[0][input.size() - 1].end(), cfg.getStartSymbol()) !=
           table[0][input.size() - 1].end();
}

