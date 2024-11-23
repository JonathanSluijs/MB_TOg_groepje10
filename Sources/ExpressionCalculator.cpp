//
// Created by cain on 23/11/24.
//

#include "../Headers/ExpressionCalculator.h"
#include <functional>
#include <unordered_map>
#include <stdexcept>
#include <cmath>
#include <stack>

// TODO: change lamda functions to use TM
std::unordered_map<char, std::function<double(double, double)>> operations = {{'+', [](double a, double b) {
    return a + b;
}},
                                                                              {'-', [](double a, double b) {
                                                                                  return a - b;
                                                                              }},
                                                                              {'*', [](double a, double b) {
                                                                                  return a * b;
                                                                              }},
                                                                              {'/', [](double a, double b) {
                                                                                  if (b != 0) return a / b;
                                                                                  throw std::runtime_error(
                                                                                          "Division by zero");
                                                                              }},
                                                                              {'^', [](double a, double b) {
                                                                                  return std::pow(a, b);
                                                                              }}};

/**
 * Convert the expression to infix notation using shunting yard algorithm
 */
void ExpressionCalculator::toPostfix() {
    std::string output;
    std::stack<char> operators;

    // Loop through the expression
    for (char c: expression) {
        // If the character is a digit, add it to the output
        if (isdigit(c)) {
            output += c;
        } else {
            // If the character is a left parenthesis, add it to the output
            if (c == '(') {
                operators.push(c);
            } else if (c == ')') {
                // The character is a right parenthesis
                // Pop from the stack and add to output until top is left parenthesis or empty stack
                while (!operators.empty() && operators.top() != '(') {
                    output += operators.top();
                    operators.pop();
                }
                operators.pop();
            } else {
                // The character is an operator
                if (c == '+' || c == '-') {
                    // Check if there is an operator at top of the stack with greater precedence
                    while (!operators.empty() && (operators.top() == '*' || operators.top() == '/' || operators.top() == '^')) {
                        output += operators.top();
                        operators.pop();
                    }
                    operators.push(c);
                } else if (c == '/' || c == '*') {
                    // Check if there is an operator at top of the stack with greater precedence
                    while (!operators.empty() && operators.top() == '^') {
                        output += operators.top();
                        operators.pop();
                    }
                    operators.push(c);
                } else {
                    operators.push(c);
                }
            }
        }
    }
    while (!operators.empty()) {
        output += operators.top();
        operators.pop();
    }
    expression = output;
}

/**
 * Calculate the result of the expression
 * @return the result of the expression
 */
double ExpressionCalculator::calculate() {
    // Stack used to calculate expression
    std::stack<double> stack;

    // Convert infix expression to postfix
    toPostfix();

    // Loop over characters of the postfix expression
    for (char c: expression) {
        // If the character is a digit, push it to the stack
        if (isdigit(c)) {
            stack.push(c - '0');
        } else {
            // The character is an operator
            // Pop two operands from the stack
            double operand2 = stack.top();
            stack.pop();
            double operand1 = stack.top();
            stack.pop();

            // Perform the operation and push the result to the stack
            stack.push(operations[c](operand1, operand2));
        }
    }
    return stack.top();
}


