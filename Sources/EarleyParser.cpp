//
// Created by emir on 11/17/24.
//

#include "../Headers/EarleyParser.h"

parser::EarleyParser & parser::EarleyParser::getInstance() {
    static EarleyParser _instance;
    return _instance;
}

bool parser::EarleyParser::parse(const std::string &input, const CFG &cfg) {
    bool valid_input = false;
    unsigned int set_number = 0;
    for(const char& cur_char : input) {
        // Do something
    }
    return valid_input;
}

int parser::EarlyItem::getDotPosition() const {
    return dot_position;
}

void parser::EarlyItem::setDotPosition(int dot_position) {
    this->dot_position = dot_position;
}

const std::vector<std::string> & parser::EarlyItem::getProduction() const {
    return production;
}

void parser::EarlyItem::setProduction(const std::vector<std::string> &production) {
    this->production = production;
}

int parser::EarlyItem::getStartingPoint() const {
    return starting_point;
}

void parser::EarlyItem::setStartingPoint(int starting_point) {
    this->starting_point = starting_point;
}
