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
    // Make sure the stack is empty
    while (!postfix.empty()) {
        postfix.pop();
    }
    std::stack<std::string> operators;

    // Loop through the expression
    for (std::string s: tokenizeExpression(expression)) {
        // If the character is a digit, add it to the output
        if (isdigit(s[0])) {
            postfix.push(s);
        } else {
            // If the character is a left parenthesis, add it to the output
            if (s == "(") {
                operators.push(s);
            } else if (s == ")") {
                // The character is a right parenthesis
                // Pop from the stack and add to output until top is left parenthesis or empty stack
                while (!operators.empty() && operators.top() != "(") {
                    postfix.push(operators.top());
                    operators.pop();
                }
                operators.pop();
            } else {
                // The character is an operator
                while (!operators.empty() && precedence(s) < precedence(operators.top()) ||
                       !operators.empty() && precedence(s) == precedence(operators.top())) {
                    postfix.push(operators.top());
                    operators.pop();
                }
                operators.push(s);
            }
        }
    }
    while (!operators.empty()) {
        postfix.push(operators.top());
        operators.pop();
    }
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
    while (!postfix.empty()) {
        // If the character is a digit, push it to the stack
        if (isdigit(postfix.front()[0])) {
            stack.push(std::stod(postfix.front()));
            postfix.pop();
        } else {
            // The character is an operator
            // Pop two operands from the stack
            double operand2 = stack.top();
            stack.pop();
            double operand1 = stack.top();
            stack.pop();

            // Perform the operation and push the result to the stack
            stack.push(operations[postfix.front()[0]](operand1, operand2));
            postfix.pop();
        }
    }
    return stack.top();
}

/**
 * Tokenize the expression
 * @param expression the expression to tokenize
 * @return the tokens of the expression
 */
std::vector<std::string> ExpressionCalculator::tokenizeExpression(const std::string &expression) {
    std::vector<std::string> tokens;
    std::string currentToken;

    for (char ch : expression) {
        if (std::isdigit(ch)) {
            // If the character is a digit, add it to the current token
            currentToken += ch;
        } else {
            // If the character is not a digit, it's likely an operator or a delimiter
            if (!currentToken.empty()) {
                tokens.push_back(currentToken); // Add the current number token
                currentToken.clear();           // Reset the current token
            }
            tokens.push_back(std::string(1, ch)); // Add the operator or symbol as a token
        }
    }

    // Add the last token if it's a number
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

int ExpressionCalculator::precedence(const std::string &s) {
    if (s == "^")
        return 3;
    else if (s == "/" || s == "*")
        return 2;
    else if (s == "+" || s == "-")
        return 1;
    else
        return -1; // Return -1 for invalid or unsupported operators
}


