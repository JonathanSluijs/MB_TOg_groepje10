//
// Created by Jonat on 01/11/2024.
//
#include "../Headers/Tape.h"

Tape::Tape() : headPosition(0) { tape.push_back('_'); }

void Tape::write(char symbol) { tape[headPosition] = symbol; }

char Tape::read() { return tape[headPosition]; }

std::string Tape::readAll() {
    std::string content;
    for (char c : tape) content += c;
    return content;
}

void Tape::move(Direction dir) {
    if (dir == LEFT) {
        if (headPosition == 0) tape.push_front('_');              // Expand tape left
        else headPosition--;
    } else if (dir == RIGHT) {
        headPosition++;
        if (headPosition == tape.size()) tape.push_back('_');     // Expand tape right
    }
}

void Tape::print() const {
    for (char c : tape) std::cout << c;
    std::cout << " (head at " << headPosition << ")\n";
}

void Tape::setContent(const std::string& content) {
    tape.clear();  // Clear current tape content
    for (char c : content) {
        tape.push_back(c);  // Add each character to the tape
    }


    headPosition = 0;
}

std::string Tape::getContent() const {
    std::string content;
    for (char c : tape) content += c;
    return content;
}
