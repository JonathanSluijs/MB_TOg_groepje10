//
// Created by emir on 11/16/24.
//

#include "TuringSimulationDialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QRegularExpressionValidator>

TuringSimulationDialog::TuringSimulationDialog(QWidget *parent) {
    setMinimumSize(QSize(720, 720));
    setWindowTitle("Turing Machine Simulator");
    createGraphics();
    createEvents();
}


void TuringSimulationDialog::createGraphics() {
    setStyleSheet("background-color: #B2DFDB;");

    QGridLayout *layout = new QGridLayout(this);

    // Create the input field for the expression
    // Create a regular expression to only allow numbers 1-9 and certain operators
    expression_input = new QLineEdit(this);
    expression_input->setStyleSheet("border: 3px solid blue; padding: 5px;");
    limitCharacters();

    // Create the submit button
    submit_button = new QPushButton("Submit", this);
    submit_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    submit_button->setStyleSheet("background-color: blue; color: white;");

    // Create radio buttons for the algorithms
    cyk_algorithm = new QRadioButton("CYK parsing", this);
    earley_algorithm = new QRadioButton("Earley parsing", this);

    cyk_algorithm->setChecked(true);

    // Create text field for information
    QLabel* parser_info = new QLabel("Choose the parsing algorithm you want to use to validate the expressions.", this);
    QLabel* input_info = new QLabel(
        "Insert your math expression in the box below. You can only use the following operators: +, -, *, /, ^, (, )."
        , this);

    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(parser_info, 0, 0);
    layout->addWidget(cyk_algorithm, 1, 0);
    layout->addWidget(earley_algorithm, 2, 0);
    layout->addWidget(input_info, 3, 0);
    layout->addWidget(expression_input, 4, 0);
    layout->addWidget(submit_button, 5, 0);
}

void TuringSimulationDialog::createEvents() const {
    QObject::connect(submit_button, SIGNAL(clicked()), this,  SLOT(submitExpression()));
}

void TuringSimulationDialog::limitCharacters() {
    if (expression_input) {
        const QRegularExpression regex("^[0-9+\\-*/^()]*$"); // Choose the characters that are allowed
        QValidator *validator = new QRegularExpressionValidator(regex, expression_input);
        expression_input->setValidator(validator);
    }
}

//TODO: Implement the submitExpression function
void TuringSimulationDialog::submitExpression() {
    bool valid = true;

    // Check which parsing algorithm is selected
    if(cyk_algorithm->isChecked()){
        //Do something
    }else if(earley_algorithm->isChecked()){
        //Do something else
    }
}
