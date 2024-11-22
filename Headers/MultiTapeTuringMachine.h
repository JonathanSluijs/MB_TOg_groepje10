//
// Created by Jonat on 01/11/2024.
//

#ifndef MB_TOG_GROEPJE10_MULTITAPETURINGMACHINE_H
#define MB_TOG_GROEPJE10_MULTITAPETURINGMACHINE_H

// Project files
#include "Tape.h"
#include "TransitionFunction.h"

// Dependencies
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <tuple>

/**
 * @brief Represents a multi-tape Turing machine.
 *
 * This class models a Turing machine with multiple tapes, each of which can
 * be independently read from and written to. It allows for simulating computations
 * as defined in the theory of Turing machines, making it a powerful model for
 * understanding the limits of computation.
 */
class MultiTapeTuringMachine {
private:
    /// Number of tapes in the Turing machine.
    int numTapes;

    /// Vector of tapes used by the Turing machine.
    std::vector<Tape> tapes;

    /// Current state of the Turing machine.
    std::string currentState;

    /// Accept state, representing a successful end of computation.
    std::string acceptState;

    /// Reject state, representing a failed end of computation.
    std::string rejectState;

    /// Transition function defining the state transitions for the machine.
    TransitionFunction transitionFunction;

public:
    /**
     * @brief Constructs a multi-tape Turing machine.
     *
     * Initializes a Turing machine with the given number of tapes, initial state,
     * accept state, and reject state.
     *
     * @param tapesCount Number of tapes in the Turing machine.
     * @param startState Initial state of the Turing machine.
     * @param accept Accept state, where the machine halts and accepts the input.
     * @param reject Reject state, where the machine halts and rejects the input.
     */
    MultiTapeTuringMachine(int tapesCount, const std::string& startState, const std::string& accept, const std::string& reject);

    /**
     * @brief Sets the transition function for the Turing machine.
     *
     * The transition function dictates how the machine moves from one state to another
     * based on the current state and tape symbols being read.
     *
     * @param tf The transition function to be set for the machine.
     */
    void setTransitionFunction(const TransitionFunction& tf);

    /**
     * @brief Runs the Turing machine on the input tapes.
     *
     * This function processes the input using the current state and transition function.
     * The machine continues running until it reaches either the accept or reject state.
     *
     * @return True if the machine reaches the accept state, otherwise false.
     */
    bool run();

    /**
     * @brief Prints the current content of all tapes.
     *
     * Outputs the contents of each tape to the console. Useful for debugging or understanding
     * the progress of the Turing machine during execution.
     */
    void printTapes() const;

    /**
     * @brief Retrieves a tape by its index.
     *
     * Provides access to a specific tape for reading or writing.
     *
     * @param index Index of the tape to retrieve (starting from 0).
     * @return Reference to the requested tape.
     * @throws std::out_of_range if the index is out of valid range.
     */
    Tape& getTape(int index);

    /**
     * @brief Copies the symbol currently under the tape head from one tape to another.
     *
     * This method copies the current symbol from the head of a source tape to a target tape.
     * This can be useful for operations involving multiple tapes where values need to be shared.
     *
     * @param from Index of the source tape to read the symbol from.
     * @param to Index of the target tape to write the symbol to.
     */
    void copyTapeSymbol(int from, int to);
};

#endif //MB_TOG_GROEPJE10_MULTITAPETURINGMACHINE_H
