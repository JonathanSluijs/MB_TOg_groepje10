//
// Created by Jonat on 01/11/2024.
//

#include "MultiTapeTuringMachine.h"

int main(int argc, char *argv[]) {
    // Create a MultiTapeTuringMachine instance with 3 tapes:
    // - Tape 1: Input expression (e.g., "3+(4*5)-6")
    // - Tape 2: Parentheses stack
    // - Tape 3: Token type tracking (to ensure correct token order)
    MultiTapeTuringMachine machine(3, "q0", "q_accept", "q_reject");

    // Transitions
    TransitionFunction tf;
    tf.addTransition("q0", {'3', '_', '_'}, "q_operand", {'3', '_', 'N'}, {RIGHT, STAY, STAY});
    tf.addTransition("q_operand", {'+', '_', 'N'}, "q_operator", {'+', '_', 'O'}, {RIGHT, STAY, STAY});
    tf.addTransition("q_operator", {'(', '_', 'O'}, "q_push", {'(', '(', 'O'}, {RIGHT, RIGHT, STAY});
    tf.addTransition("q_push", {'4', '_', 'O'}, "q_operand", {'4', '_', 'N'}, {RIGHT, STAY, STAY});
    tf.addTransition("q_operand", {'*', '_', 'N'}, "q_operator", {'*', '_', 'O'}, {RIGHT, STAY, STAY});
    tf.addTransition("q_operator", {'5', '_', 'O'}, "q_operand", {'5', '_', 'N'}, {RIGHT, STAY, STAY});
    tf.addTransition("q_operand", {')', '_', 'N'}, "q_find_open", {')', '_', 'N'}, {STAY, RIGHT, STAY});
    tf.addTransition("q_find_open", {')', '(', 'N'}, "q_pop", {')', '_', 'N'}, {RIGHT, STAY, STAY});
    tf.addTransition("q_pop", {'-', '_', 'N'}, "q_operator", {'-', '_', 'O'}, {RIGHT, STAY, STAY});
    tf.addTransition("q_operator", {'6', '_', 'O'}, "q_operand", {'6', '_', 'N'}, {RIGHT, STAY, STAY});
    tf.addTransition("q_operand", {'_', '_', 'N'}, "q_check", {'_', '_', 'N'}, {STAY, STAY, STAY});
    tf.addTransition("q_check", {'_', '_', 'N'}, "q_accept", {'_', '_', 'N'}, {STAY, STAY, STAY});
    tf.addTransition("q_check", {'_', '(', 'N'}, "q_reject", {'_', '(', 'N'}, {STAY, STAY, STAY});

    tf.addTransition("q_operand", {')', '(', 'N'}, "q_pop", {')', '_', 'N'}, {RIGHT, LEFT, STAY});
    tf.addTransition("q_pop", {'-', '_', 'N'}, "q_operator", {'-', '_', 'O'}, {RIGHT, STAY, STAY});
    tf.addTransition("q_operator", {'6', '_', 'O'}, "q_operand", {'6', '_', 'N'}, {RIGHT, STAY, STAY});
    tf.addTransition("q_operand", {'_', '_', 'N'}, "q_check", {'_', '_', 'N'}, {STAY, STAY, STAY});
    tf.addTransition("q_check", {'_', '_', 'N'}, "q_accept", {'_', '_', 'N'}, {STAY, STAY, STAY});
    tf.addTransition("q_check", {'_', '(', 'N'}, "q_reject", {'_', '(', 'N'}, {STAY, STAY, STAY});
    tf.addTransition("q_operator", {'(', '_', 'O'}, "q_push", {'(', '(', 'O'}, {RIGHT, LEFT, STAY});




    // Set the transition function for the machine
    machine.setTransitionFunction(tf);

    // Set up the input expression on Tape 1
    // Tape 1 contains the entire input expression to validate
    machine.getTape(0).setContent("3+(4*5)-6");

    // Initialize Tape 2 and Tape 3 as empty
    machine.getTape(1).setContent("_");  // Parentheses stack (initially empty)
    machine.getTape(2).setContent("_");  // Token type tracking (initially empty)

    // Print initial tape states for debugging
    std::cout << "Initial Tapes:\n";
    machine.printTapes();

    // Run
    if (machine.run()) {
        std::cout << "Machine accepted the expression. The expression is valid.\n";
    } else {
        std::cout << "Machine rejected the expression. The expression is invalid.\n";
    }

    machine.printTapes();

    return 0;
}
