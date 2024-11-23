//
// Created by emir on 11/16/24.
//

#include "ArithmeticDialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include "../Parsers//CYKParser.h"
#include "../Headers/CFG.h"
#include "../Headers/ExpressionCalculator.h"

ArithmeticDialog::ArithmeticDialog(const std::string &grammar_file, QWidget *parent) {
    setMinimumSize(QSize(720, 720));
    setWindowTitle("Math Expression Calculator");
    createGraphics();
    createEvents();
    cfg = new CFG{grammar_file};
}

ArithmeticDialog::~ArithmeticDialog() {
    delete cfg;
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
            "Insert your math expression in the box below. You can only use the following operators: +, -, *, /, ^, (, ).",
            this);

    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(input_info, 0, 0);
    layout->addWidget(expression_input, 2, 0);
    layout->addWidget(submit_button, 3, 0);
}

void ArithmeticDialog::createEvents() const {
    QObject::connect(submit_button, SIGNAL(clicked()), this, SLOT(submitExpression()));
}


void ArithmeticDialog::notValidated() {
    QMessageBox::warning(this, "Invalid Expression",
                         "The expression you entered is not valid. Please try again.\nUnary operators are not supported.\nWrite (1+1)(1+1) as (1+1)*(1+1).");
}

void ArithmeticDialog::limitCharacters() const {
    if (expression_input) {
        const QRegularExpression regex("^[0-9+\\-*/^()]*$"); // Choose the characters that are allowed
        QValidator *validator = new QRegularExpressionValidator(regex, expression_input);
        expression_input->setValidator(validator);
    }
}

// TODO: Implement the submitExpression function
void ArithmeticDialog::submitExpression() {

    // If there is no input
    if (expression_input->text().isEmpty()) {
        QMessageBox::warning(this, "Empty Expression", "Please enter an expression.");
        return;
    }

    if (parser::CYKParser::getInstance().parse(expression_input->text().toStdString(), *cfg)) {
        QMessageBox::information(this, "Valid expression", "Expression is valid!");
        // Calculate the expression
        ExpressionCalculator calc(expression_input->text().toStdString());
        // Display the result
        QMessageBox::information(this, "Result", QString::number(calc.calculate()));
    } else {
        notValidated();
    }
}