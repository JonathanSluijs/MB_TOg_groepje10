//
// Created by cain on 23/11/24.
//

#ifndef MB_TOG_GROEPJE10_EXPRESSIONCALCULATOR_H
#define MB_TOG_GROEPJE10_EXPRESSIONCALCULATOR_H

#include <string>
#include <utility>
#include <vector>
#include <queue>

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
    std::queue<std::string> postfix;
public:
    /**
     * Constructor
     * @param expression the infix expression to calculate
     * @pre the expression is a valid mathematical expression checked with our CFG
     */
    explicit ExpressionCalculator(std::string expression) : expression(std::move(expression)) {};

    /**
     * Calculate the result of the expression using shunting yard algorithm
     * @pre the expression does not contain division by zero
     * @return the result of the expression
     */
    double calculate();
private:
    /**
     * Tokenize the expression
     * @param expression the expression to tokenize
     * @return the tokens of the expression
     */
    std::vector<std::string> tokenizeExpression(const std::string& expression);

    /**
     * Convert the expression to infix notation using shunting yard algorithm
     */
    void toPostfix();

    int precedence(const std::string& s);

};


#endif //MB_TOG_GROEPJE10_EXPRESSIONCALCULATOR_H
