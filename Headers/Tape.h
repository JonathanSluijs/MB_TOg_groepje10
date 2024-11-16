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
    // Tape content
    // using deque for constant-time access and efficient insertions at both ends
    std::deque<char> tape;
    int headPosition;

public:
    // Default constructor for the Tape class
    // Initializes the tape with a single blank symbol ('_') and sets the head position to 0.
    Tape();

    // Reads and returns the symbol under the tape head
    // Returns:
    // - The character at the current head position in the tape.
    char read();

    // Writes a symbol under the tape head, replacing any existing symbol in that position.
    // Parameters:
    // - symbol: The character to write at the current head position on the tape.
    void write(char symbol);

    // Moves the tape head in the specified direction, expanding the tape if necessary.
    // Parameters:
    // - dir: The direction to move the head (LEFT, RIGHT, or STAY).
    //   - If LEFT, moves the head left; if at the beginning of the deque, inserts a blank symbol ('_') at the front.
    //   - If RIGHT, moves the head right; if at the end of the deque, appends a blank symbol ('_') at the back.
    void move(Direction dir);               // Move the head in the specified direction

    // Prints the entire tape content and indicates the current head position.
    // Used mainly for debugging purposes to visualize the tape’s state.
    void print() const;                     // Print the current tape content

    // Sets the content of the tape to a given string and resets the head position.
    // Parameters:
    // - content: A string representing the initial content of the tape.
    // - The head is positioned at the last character of the content to represent the least significant bit in binary numbers,
    //   or at 0 if the content is empty.
    void setContent(const std::string& content);






};


#endif //MB_TOG_GROEPJE10_TAPE_H
