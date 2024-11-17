//
// Created by emir on 11/17/24.
//

#include "../Headers/EarleyParser.h"

parser::EarleyParser & parser::EarleyParser::getInstance() {
    static EarleyParser _instance;
    return _instance;
}

void parser::EarleyParser::parse(const std::string &input, const CFG &cfg) {
}
