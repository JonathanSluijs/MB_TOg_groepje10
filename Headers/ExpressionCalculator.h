//
// Created by cain on 23/11/24.
//

#ifndef MB_TOG_GROEPJE10_EXPRESSIONCALCULATOR_H
#define MB_TOG_GROEPJE10_EXPRESSIONCALCULATOR_H

#include <string>
#include <utility>

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
public:
    /**
     * Constructor
     * @param expression the infix expression to calculate
     * @pre the expression is a valid mathematical expression checked with our CFG
     */
    explicit ExpressionCalculator(std::string expression) : expression(std::move(expression)) {};

    /**
     * Convert the expression to infix notation using shunting yard algorithm
     */
    void toPostfix();

    /**
     * Calculate the result of the expression using shunting yard algorithm
     * @pre the expression does not contain division by zero
     * @return the result of the expression
     */
    double calculate();

    /**
     * Get the expression
     * @return the expression
     */
    [[nodiscard]] std::string getExpression() const {
        return expression;
    }

};


#endif //MB_TOG_GROEPJE10_EXPRESSIONCALCULATOR_H
