#ifndef MB_TOG_GROEPJE10_SINGLETAPETRANSFORMER_H
#define MB_TOG_GROEPJE10_SINGLETAPETRANSFORMER_H

// Dependencies
#include "../Headers/Tape.h"
#include "../Headers/TransitionFunction.h"
#include "../Headers/Logger.h"
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
/**
 * @brief Transforms multiple tapes into a single 2D array representation and runs computations.
 *
 * This class is designed to process multiple tapes used in a Turing machine
 * by transforming them into a unified representation. It provides methods
 * for running computations using a transition function and visualizing the
 * state of the tapes in a 2D array format, making it suitable for debugging.
 */
class SingleTapeTransformer {
private:
    /// A collection of tapes to be transformed and processed.
    std::vector<Tape> tapes;
   std::vector<Tape> headPointerTapes; // Tapes to track head pointer positions

    /// The current state of the Turing machine during execution.
    std::string currentState;

    /// The accept state, where the machine halts with a positive outcome.
    std::string acceptState;

    /// The reject state, where the machine halts with a negative outcome.
    std::string rejectState;

    /// Transition function defining the rules for state transitions.
    TransitionFunction transitionFunction;

public:
    /**
     * @brief Constructs a single-tape transformer.
     *
     * Initializes the transformer with a collection of tapes, the starting
     * state, the accept state, and the reject state.
     *
     * @param tapes A vector of `Tape` objects representing the tapes to be transformed.
     * @param startState The initial state of the machine.
     * @param acceptState The state where the machine halts and accepts the input.
     * @param rejectState The state where the machine halts and rejects the input.
     */
    SingleTapeTransformer(const std::vector<Tape>& tapes, const std::string& startState, const std::string& acceptState, const std::string& rejectState);

    /**
     * @brief Sets the transition function for the transformer.
     *
     * Assigns a transition function that dictates how the machine moves
     * from one state to another based on the current state and tape symbols.
     *
     * @param tf The `TransitionFunction` to be used by the transformer.
     */
    void setTransitionFunction(const TransitionFunction& tf);

    /**
     * @brief Runs the transformer on the tapes using the transition function.
     *
     * Simulates the execution of the Turing machine using the provided
     * transition function. The machine transitions between states and processes
     * the tapes until it reaches the accept or reject state.
     *
     * @return True if the machine reaches the accept state; otherwise, false.
     */
    bool run();

    /**
     * @brief Converts the tapes into a single 2D array representation.
     *
     * Each tape is represented as two rows:
     * - The first row contains the tape's content.
     * - The second row contains a marker (`^`) indicating the tape head's position.
     *
     * @return A 2D array where each tape contributes two rows.
     */
    std::vector<std::vector<char>> to2DArray();

    /**
     * @brief Prints the 2D array representation of the tapes.
     *
     * Outputs the transformed tapes to the console, showing their content
     * and the position of the tape head. Useful for debugging and visualizing
     * the current state of the tapes.
     */
    void print2DArray();
};

#endif //MB_TOG_GROEPJE10_SINGLETAPETRANSFORMER_H