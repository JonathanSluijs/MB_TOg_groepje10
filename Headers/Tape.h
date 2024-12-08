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

/**
 * @brief Represents a tape in a Turing Machine.
 *
 * A tape is essentially an infinite sequence of cells that can store symbols. The tape head can read from and write to
 * the cells, and it can move left or right. This class provides methods to manipulate the tape, including reading, writing,
 * and moving the head.
 */
class Tape {
private:
    std::deque<char> tape;  ///< Content of the tape using a deque for efficient insertion at both ends
    int headPosition;  ///< Current position of the tape head

public:
    /**
     * @brief Default constructor for Tape.
     * Initializes the tape with a single blank symbol ('_') and sets the head position to 0.
     */
    Tape();

    /**
     * @brief Reads the symbol under the tape head.
     * @return The character at the current head position.
     */
    char read();

    /**
     * @brief Reads the entire content of the tape.
     * @return The current content of the tape as a string.
     */
    std::string readAll();

    /**
     * @brief Writes a symbol under the tape head.
     * @param symbol The character to write at the current head position.
     */
    void write(char symbol);

    /**
     * @brief Moves the tape head in the specified direction.
     * Expands the tape if necessary to accommodate the head's movement.
     * @param dir The direction to move the head (LEFT, RIGHT, or STAY).
     */
    void move(Direction dir);

    /**
     * @brief Prints the entire content of the tape.
     * Used mainly for debugging purposes to visualize the tape’s state.
     */
    void print() const;

    /**
     * @brief Sets the content of the tape to a given string and resets the head position.
     * @param content A string representing the initial content of the tape.
     */
    void setContent(const std::string& content);

    /**
     * @brief Returns the current content of the tape.
     * @return The content of the tape as a string.
     */
    std::string getContent() const;
};

#endif //MB_TOG_GROEPJE10_TAPE_H
