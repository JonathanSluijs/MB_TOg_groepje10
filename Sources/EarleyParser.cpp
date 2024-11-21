//
// Created by emir on 11/17/24.
//

#include "../Headers/EarleyParser.h"
#include "../Headers/CFG.h"
#include <iostream>

parser::EarleyParser &parser::EarleyParser::getInstance() {
    static EarleyParser _instance;
    return _instance;
}

//TODO: Fix the bugs
bool parser::EarleyParser::parse(const std::string &input, const CFG &cfg) {
    bool valid_input = false;
    std::vector<std::vector<EarlyItem> > state_sets;

    // Initialize the first set
    std::vector<EarlyItem> initial_set;
    std::map<std::string, std::vector<std::vector<std::string> > > productions = cfg.getProductions();
    const std::string &start_symbol = cfg.getStartSymbol();

    for (const auto &production: productions[start_symbol]) {
        initial_set.emplace_back(0, start_symbol, production, 0);
        std::cout << "LOG::Initial Early Items toegevoegd" << std::endl;
    }
    state_sets.push_back(initial_set);

    // Main Loop
    size_t i = 0;
    for (const char &cur_char: input) {
        while (i < state_sets.size()) {
            size_t j = 0;
            std::vector<EarlyItem> current_set = state_sets[i];
            while (j < current_set.size()) {
                /**If the item is a confirmed success, search the predictions**/
                if (current_set[j].confirmedSuccess()) {
                    int starting_point = current_set[j].StartPoint();
                    for (size_t k = 0; k < state_sets[starting_point].size(); ++k) {
                        if (state_sets[starting_point][k].Current() == current_set[j].Head()) {
                            addUnique(current_set, EarlyItem(state_sets[starting_point][k].Dot() + 1,
                                                             state_sets[starting_point][k].Head(),
                                                             state_sets[starting_point][k].Body(), starting_point));
                        }
                    }
                    j++;
                    state_sets[i] = current_set;
                    continue;
                }
                const std::string cur_symbol = current_set[j].Current();
                if (cfg.isVariable(cur_symbol)) {
                    /**********The predict function************/
                    for (const auto &production: productions[cur_symbol]) {
                        if (addUnique(current_set, EarlyItem(i, cur_symbol, production, i))) {
                            std::cout << "current set length" << current_set.size() << std::endl;
                            std::cout << "LOG::Prediction" << std::endl;
                        };
                    }
                } else if (cfg.isTerminal(cur_symbol)) {
                    /**********The scan function****************/
                    if (cur_symbol[0] == cur_char) {
                        if (state_sets.size() <= i + 1) {
                            state_sets.resize(i + 2); // Vergroot de vector tot minstens i+1
                        }
                        state_sets[i + 1].emplace_back(current_set[j].Dot() + 1, current_set[j].Head(),
                                                       current_set[j].Body(), i);
                        std::cout << "LOG::Scan" << std::endl;
                    }
                } else {
                    return false;
                }
                j++;
                state_sets[i] = current_set;
            }
            i++;
        }
    }

    for (size_t s = 0; s < state_sets[state_sets.size() - 1].size(); ++s) {
        if (state_sets[state_sets.size() - 1][s].StartPoint() == 0 && state_sets[state_sets.size() - 1][s].
            confirmedSuccess() && state_sets[state_sets.size() - 1][s].Head() == cfg.getStartSymbol()) {
            valid_input = true;
        }
    }

    return valid_input;
}


parser::EarlyItem::EarlyItem(unsigned int dot, const std::string &head, const std::vector<std::string> &body,
                             unsigned int starting_point): dot(dot), head(head),
                                                           body(body),
                                                           starting_point(starting_point) {
}

parser::EarlyItem::EarlyItem(const EarlyItem &other): dot(other.dot), head(other.head), body(other.body),
                                                      starting_point(other.starting_point) {
}

bool parser::EarlyItem::operator==(const EarlyItem &other) const {
    return body == other.body && dot == other.dot && starting_point == other.starting_point;
}

unsigned int parser::EarlyItem::Dot() const {
    return dot;
}

const std::string &parser::EarlyItem::Head() const {
    return head;
}

const std::vector<std::string> &parser::EarlyItem::Body() const {
    return body;
}

const std::string &parser::EarlyItem::Current() const {
    return body[dot];
}

unsigned int parser::EarlyItem::StartPoint() const {
    return starting_point;
}

bool parser::EarlyItem::confirmedSuccess() const {
    return dot >= body.size();
}

