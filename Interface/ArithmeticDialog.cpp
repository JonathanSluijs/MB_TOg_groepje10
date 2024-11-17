//
// Created by emir on 11/16/24.
//

#include "ArithmeticDialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include "../Headers/CYKParser.h"
#include "../Headers/CFG.h"

ArithmeticDialog::ArithmeticDialog(QWidget *parent) {
    setMinimumSize(QSize(720, 720));
    setWindowTitle("Math Expression Calculator");
    createGraphics();
    createEvents();
}

void ArithmeticDialog::createGraphics() {
    setStyleSheet("background-color: #B2DFDB;");

    layout = new QGridLayout(this);

    // Create the input field for the expression
    // Create a regular expression to only allow numbers 1-9 and certain operators
    expression_input = new QLineEdit(this);
    expression_input->setStyleSheet("border: 3px solid blue; padding: 5px;");
    limitCharacters();

    // Create the submit button
    submit_button = new QPushButton("Submit", this);
    submit_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    submit_button->setStyleSheet("background-color: blue; color: white;");

    // Create text field for
    input_info = new QLabel(
        "Insert your math expression in the box below. You can only use the following operators: +, -, *, /, ^, (, )."
        , this);

    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(input_info, 0, 0);
    layout->addWidget(expression_input, 2, 0);
    layout->addWidget(submit_button, 3, 0);
}

void ArithmeticDialog::createEvents() const {
    QObject::connect(submit_button, SIGNAL(clicked()), this, SLOT(submitExpression()));
}


void ArithmeticDialog::notValidated() {
    QMessageBox::warning(this, "Invalid Expression", "The expression you entered is not valid. Please try again.");
}

void ArithmeticDialog::limitCharacters() const {
    if (expression_input) {
        const QRegularExpression regex("^[0-9+\\-*/^()]*$"); // Choose the characters that are allowed
        QValidator *validator = new QRegularExpressionValidator(regex, expression_input);
        expression_input->setValidator(validator);
    }
}

#include <iostream>
// TODO: Implement the submitExpression function
// TODO: CNF and CFG are not right, need to fix them
void ArithmeticDialog::submitExpression() {
    CFG cfg("../InputFiles/expressionCNF.json");

    std::cout << expression_input->text().toStdString() << std::endl;
    if (parser::CYKParser::getInstance().parse(expression_input->text().toStdString(), cfg)) {
        // Calculate the expression
        // Display the result
    } else {
        notValidated();
    }
}
