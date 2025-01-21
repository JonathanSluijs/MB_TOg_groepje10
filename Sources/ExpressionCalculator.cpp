//
// Created by cain on 23/11/24.
//

#include "../Headers/ExpressionCalculator.h"
#include <functional>
#include <unordered_map>
#include <stdexcept>
#include <cmath>

std::string ExpressionCalculator::intToOnes(int a) {
    std::string result;
    for (int i = 0; i < a; i++) {
        result += "1";
    }
    return result;
}

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
 */
int ExpressionCalculator::calculate() {
    // Initialize the MTMs if not initialized
    if (!MTMInitialized) {
        initializeMTM();
    }

    // Stack used to calculate expression
    std::stack<int> stack;

    // Convert infix expression to postfix
    toPostfix();

    // Convert postfix expression to infix, to show precedence in steps
    toInfix(stack);

    // Loop over characters of the postfix expression
    while (!postfix.empty()) {
        // If the character is a digit, push it to the stack
        if (isdigit(postfix.front()[0])) {
            stack.push(std::stod(postfix.front()));
            postfix.pop();
        } else {
            // The character is an operator
            // Pop two operands from the stack
            int operand2 = stack.top();
            stack.pop();
            int operand1 = stack.top();
            stack.pop();

            // Perform the operation and push the result to the stack
            stack.push(operations[postfix.front()[0]](operand1, operand2));
            postfix.pop();
            // Convert postfix expression to infix, to show steps
            toInfix(stack);
        }
    }
    steps.push_back(std::to_string(stack.top()));
    return stack.top();
}

/**
 * Tokenize the expression
 * @param expression the expression to tokenize
 * @return the tokens of the expression
 */
std::vector<std::string> ExpressionCalculator::tokenizeExpression(const std::string &expr) {
    std::vector<std::string> tokens;
    std::string currentToken;

    for (char ch: expr) {
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
    if (s == "(")
        return 0;
    else if (s == "^")
        return 3;
    else if (s == "/" || s == "*")
        return 2;
    else if (s == "+" || s == "-")
        return 1;
    else
        return -1; // Return -1 for invalid or unsupported operators
}

void ExpressionCalculator::initializeMTM() {
    TransitionFunction plusTF = parseTransitionFile("../InputFiles/TransitionFiles/additionMTM.json");
    plusMTM.setTransitionFunction(plusTF);

    TransitionFunction minusTF = parseTransitionFile("../InputFiles/TransitionFiles/subtractionMTM.json");
    minusMTM.setTransitionFunction(minusTF);

    TransitionFunction multiplyTF = parseTransitionFile("../InputFiles/TransitionFiles/multiplicationMTM.json");
    multiplyMTM.setTransitionFunction(multiplyTF);

    TransitionFunction divideTF = parseTransitionFile("../InputFiles/TransitionFiles/divisionMTM.json");
    divideMTM.setTransitionFunction(divideTF);

    TransitionFunction powerTF = parseTransitionFile("../InputFiles/TransitionFiles/powerMTM.json");
    powerMTM.setTransitionFunction(powerTF);

    MTMInitialized = true;
}

int ExpressionCalculator::plus(int a, int b) {
    plusMTM.reset();
    plusMTM.getTape(0).setContent(intToOnes(a) + "+" + intToOnes(b));
    plusMTM.getTape(1).setContent("_");
    plusMTM.run();
    return onesToInt(plusMTM.getTape(1).getContent());
}

int ExpressionCalculator::onesToInt(const std::string &ones) {
    int result = 0;
    for (char c: ones) {
        if (c == '1') {
            result++;
        }
    }
    return result;
}

int ExpressionCalculator::minus(int a, int b) {
    minusMTM.reset();
    minusMTM.getTape(0).setContent(intToOnes(a) + "-" + intToOnes(b));
    minusMTM.getTape(1).setContent("_");
    bool succes = minusMTM.run();
    if (!succes) {
        return -1;
    }
    return onesToInt(minusMTM.getTape(1).getContent());
}

int ExpressionCalculator::multiply(int a, int b) {
    multiplyMTM.reset();
    multiplyMTM.getTape(0).setContent(intToOnes(a));
    multiplyMTM.getTape(1).setContent(intToOnes(b));
    multiplyMTM.getTape(2).setContent("_");
    multiplyMTM.run();
    return onesToInt(multiplyMTM.getTape(2).getContent());
}

int ExpressionCalculator::divide(int a, int b) {
    divideMTM.reset();
    divideMTM.getTape(0).setContent(intToOnes(a));
    divideMTM.getTape(1).setContent(intToOnes(b));
    bool succes = divideMTM.run();
    if (!succes) {
        return -1;
    }
    return onesToInt(divideMTM.getTape(3).getContent());
}

int ExpressionCalculator::power(int a, int b) {
    powerMTM.reset();
    powerMTM.getTape(0).setContent(intToOnes(a));
    powerMTM.getTape(1).setContent(intToOnes(b));
    powerMTM.getTape(2).setContent("_");
    powerMTM.getTape(3).setContent("_");
    bool succes = powerMTM.run();
    if (!succes) {
        return -1;
    }
    return onesToInt(powerMTM.getTape(3).getContent());
}

ExpressionCalculator::ExpressionCalculator(std::string expression) : expression(std::move(expression)) {
    operations = {{'+', [this](int a, int b) {
        return plus(a, b);
    }},
                  {'-', [this](int a, int b) {
                      int result = minus(a, b);
                      if (result == -1) {
                          throw std::invalid_argument("Negative result");
                      }
                      return result;
                  }},
                  {'*', [this](int a, int b) {
                      return multiply(a, b);
                  }},
                  {'/', [this](int a, int b) {
                      int result = divide(a, b);
                      if (result == -1) {
                          throw std::invalid_argument("Division by zero");
                      }
                      return result;
                  }},
                  {'^', [this](int a, int b) {
                      int result = power(a, b);
                      if (result == -1) {
                          throw std::invalid_argument("Negative exponent");
                      }
                      return result;
                  }}};
}

void ExpressionCalculator::toInfix(std::stack<int> calcStack) {
    std::queue<std::string> postfixCopy = postfix;

    if (postfix.empty()) {
        return;
    }

    // Stack used to calculate expression
    std::stack<std::string> stack;

    std::vector<std::string> calcStackStrs(calcStack.size());
    for (int i = calcStack.size() - 1; i >= 0; i--) {
        calcStackStrs[i] = std::to_string(calcStack.top());
        calcStack.pop();
    }

    for (const std::string &s: calcStackStrs) {
        stack.push(s);
    }

    // Loop over characters of the postfix expression
    while (!postfix.empty()) {
        // If the character is a digit, push it to the stack
        if (isdigit(postfix.front()[0])) {
            stack.push(postfix.front());
            postfix.pop();
        } else {
            // The character is an operator
            // Pop two operands from the stack
            std::string operand2 = stack.top();
            stack.pop();
            std::string operand1 = stack.top();
            stack.pop();

            // Perform the operation and push the result to the stack
            stack.push("(" + operand1 + postfix.front() + operand2 + ")");
            postfix.pop();
        }
    }
    expression = stack.top();
    steps.push_back(expression);
    postfix = postfixCopy;
}

void ExpressionCalculator::writeStepsToFile(const std::string &filename) {
    std::ofstream fileStream(filename);
    for (const std::string &step: steps) {
        fileStream << step << std::endl;
    }
    fileStream.close();
}

std::string ExpressionCalculator::writeStepsToString() const {
    if (steps.empty()) {
        return "No steps available";
    }
    std::string str = steps[0] + "\n";
    for (size_t i = 1; i < steps.size(); i++) {
        str += "= " + steps[i] + "\n";
    }
    return std::move(str);
}


