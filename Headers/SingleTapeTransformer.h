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
  * @brief Executes the single-tape Turing machine simulation.
  *
  * Simulates the execution of the Turing machine using the merged single-tape transitions.
  * The machine processes states and symbols on the single tape until it reaches an accept or reject state.
  *
  * @return True if the machine reaches the accept state; otherwise, false.
  */
    bool run();

 /**
  * @brief Combines all tapes into a single tape representation.
  *
  * This method merges the contents of all tapes into a single string, with each tape separated by a `#`.
  * Additionally, a second string is generated to show the head pointer positions using the `^` symbol.
  *
  * @return A vector containing two strings:
  *         - The first string represents the combined content of all tapes, separated by `#`.
  *         - The second string represents the head pointer positions, aligned with the content.
  */
 std::vector<std::string> toSingleTape();

 /**
  * @brief Prints the single-tape representation of the tapes.
  *
  * Outputs the merged content and head pointer positions of all tapes to the console in two rows:
  * - The first row displays the content of all tapes, separated by `#`.
  * - The second row displays the head pointer positions, aligned with the tape content.
  */
 void writeSingleTape();

 /**
 * @brief Merges multi-tape transitions into a single-tape representation.
 *
 * Combines the contents of all tapes into a single tape, separated by delimiters (`#`).
 * Transitions for all tapes are merged into equivalent single-tape transitions, with head movements
 * adjusted to reflect the single-tape structure. The merged transitions are stored in the transition function.
 */
 void mergeTransitionsToSimulateSingleTape();

};

#endif //MB_TOG_GROEPJE10_SINGLETAPETRANSFORMER_H