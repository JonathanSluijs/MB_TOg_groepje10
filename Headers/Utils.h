//
// Created by Jonat on 01/11/2024.
//

#ifndef MB_TOG_GROEPJE10_UTILS_H
#define MB_TOG_GROEPJE10_UTILS_H

/**
 * @brief Represents possible movement directions for the tape head in a Turing Machine.
 *
 * This enumeration defines the movement directions of a tape head in a Turing Machine:
 * - `LEFT` moves the head to the left.
 * - `RIGHT` moves the head to the right.
 * - `STAY` keeps the head in the current position.
 */
enum Direction {
    LEFT,   ///< Move the tape head to the left
    RIGHT,  ///< Move the tape head to the right
    STAY    ///< Keep the tape head at the current position
};

#endif //MB_TOG_GROEPJE10_UTILS_H
