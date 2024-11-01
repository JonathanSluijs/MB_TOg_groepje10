//
// Created by Jonat on 01/11/2024.
//

#ifndef MB_TOG_GROEPJE10_TAPE_H
#define MB_TOG_GROEPJE10_TAPE_H
// Project files
#include "Utils.h"

// Dependencies
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <tuple>


class Tape {
private:
    std::deque<char> tape;                  // Tape content
    int headPosition;                       // Position of tape head

public:
    // Constructor
    Tape();                                 // Initialize with a blank symbol

    char read();
    void write(char symbol);                // Write a symbol under the head
    void move(Direction dir);               // Move the head in the specified direction

    void print() const;                     // Print the current tape content

    void setContent(const std::string& content);






};


#endif //MB_TOG_GROEPJE10_TAPE_H
