//
// Created by cain on 23/11/24.
//

#ifndef MB_TOG_GROEPJE10_EXPRESSIONCALCULATOR_H
#define MB_TOG_GROEPJE10_EXPRESSIONCALCULATOR_H

#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
#include "MultiTapeTuringMachine.h"

/**
 * @file ExpressionCalculator.h
 * @brief This file contains the declaration of the ExpressionCalculator class
 */


/**
 * Class to calculate the result of a mathematical expression using
 */
class ExpressionCalculator {
private:
    /**
     * The expression to calculate
     */
    std::string expression;

    /**
     * The postfix notation of the expression
     */
    std::queue<std::string> postfix;

    /**
     * The steps in the calculation
     */
    std::vector<std::string> steps;
public:
    /**
     * Constructor
     * @param expression the infix expression to calculate
     * @pre the expression is a valid mathematical expression checked with our CFG
     */
    explicit ExpressionCalculator(std::string expression);

    /**
     * Calculate the result of the expression using shunting yard algorithm
     * @pre the expression does not contain division by zero
     * @return the result of the expression
     */
    void calculate();

    /**
     * Writes all steps of the calculation to a file
     */
    void writeStepsToFile(const std::string &filename);

    /**
     * Writes all steps of the calculation to a string
     */
    std::string writeStepsToString() const;


private:
    /**
     * Tokenize the expression
     * @param expression the expression to tokenize
     * @return the tokens of the expression
     */
    std::vector<std::string> tokenizeExpression(const std::string &expression);

    /**
     * Convert the expression to infix notation using shunting yard algorithm
     */
    void toPostfix();

    /**
     * Convert the expression to infix notation
     */
    void toInfix(std::stack<int> calcStack);

    /**
     * Get the precedence of an operator
     * @param s the operator
     * @return the precedence of the operator
     */
    int precedence(const std::string &s);

    /**
     * Initialize the MultiTapeTuringMachines for the operations
     */
    void initializeMTM();

    /**
     * A boolean to check if the MTM's are initialized
     */
    bool MTMInitialized = false;

    /**
     * The MultiTapeTuringMachines for the operations
     */
    MultiTapeTuringMachine plusMTM = MultiTapeTuringMachine(2, "q0", "q_accept", "q_reject");
    MultiTapeTuringMachine minusMTM = MultiTapeTuringMachine(2, "q0", "q_accept", "q_reject");
    MultiTapeTuringMachine multiplyMTM = MultiTapeTuringMachine(3, "q0", "q_accept", "q_reject");
    MultiTapeTuringMachine divideMTM = MultiTapeTuringMachine(4, "q0", "q_accept", "q_reject");
    MultiTapeTuringMachine powerMTM = MultiTapeTuringMachine(4, "q0", "q_accept", "q_reject");

    /**
     * Given a number, return the string representation of the number in amount of ones
     */
    std::string intToOnes(int a);

    /**
     * Given a string of ones, return the integer representation of the number
     */
    int onesToInt(const std::string &ones);

    /**
     * The operations for the calculator
     */
    std::unordered_map<char, std::function<double(double, double)>> operations;

    /**
     * Does the plus operation on a multi-tape turing machine
     */
    int plus(int a, int b);

    /**
     * Does the minus operation on a multi-tape turing machine
     */
    int minus(int a, int b);

    /**
     * Does the multiply operation on a multi-tape turing machine
     */
    int multiply(int a, int b);

    /**
     * Does the divide operation on a multi-tape turing machine
     */
    int divide(int a, int b);

    /**
     * Does the power operation on a multi-tape turing machine
     */
    int power(int a, int b);
};


#endif //MB_TOG_GROEPJE10_EXPRESSIONCALCULATOR_H
