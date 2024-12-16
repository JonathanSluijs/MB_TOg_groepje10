//
// Created by emir on 11/16/24.
//

#include "TuringSimulationDialog.h"
#include "../Headers/CFG.h"
#include "../Parsers//CYKParser.h"
#include <QGridLayout>
#include <QLabel>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "../Parsers//EarleyParser.h"
#include <chrono>
#include <iostream>

#include "OutputViewer.h"
#include "../Headers/ExpressionCalculator.h"


TuringSimulationDialog::TuringSimulationDialog(const std::string &CNF_file, const std::string &CFG_file,
                                               QWidget *parent) {
    setMinimumSize(QSize(720, 720));
    setWindowTitle("Turing Machine Simulator");
    createGraphics();
    createEvents();
    cnf = new CFG{CNF_file};
    cfg = new CFG{CFG_file};
}

TuringSimulationDialog::~TuringSimulationDialog() {
    delete cfg;
}


void TuringSimulationDialog::createGraphics() {
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

    // Create radio buttons for the algorithms
    cyk_algorithm = new QRadioButton("CYK parsing", this);
    earley_algorithm = new QRadioButton("Earley parsing", this);

    cyk_algorithm->setChecked(true);

    // Create text field for information
    parser_info = new QLabel("Choose the parsing algorithm you want to use to validate the expressions.", this);
    input_info = new QLabel(
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
    QObject::connect(submit_button, SIGNAL(clicked()), this,  SLOT(submitExpression())); // NOLINT(*-unused-return-value)
}

void TuringSimulationDialog::limitCharacters() const {
    if (expression_input) {
        const QRegularExpression regex("^[0-9+\\-*/^()]*$"); // Choose the characters that are allowed
        QValidator *validator = new QRegularExpressionValidator(regex, expression_input);
        expression_input->setValidator(validator);
    }
}

void TuringSimulationDialog::notValidated(){
    QMessageBox::warning(this, "Invalid Expression", "The expression you entered is not valid. Please try again.");
}


void TuringSimulationDialog::submitExpression() {

    // If there is no input
    //-------------------------
    if(expression_input->text().isEmpty()) {
        QMessageBox::warning(this, "Empty Expression", "Please enter an expression.");
        return;
    }

    bool runtTM = false;
    // Check which parsing algorithm is selected
    //-------------------------
    if(cyk_algorithm->isChecked()){
        if(parser::CYKParser::getInstance().parse(expression_input->text().toStdString(), *cnf)) {
            QMessageBox::information(this, "Valid expression", "Expression is valid!");
            runtTM= true;
        }else
            notValidated();
    }else if(earley_algorithm->isChecked()){
        if(parser::EarleyParser::getInstance().parse(expression_input->text().toStdString(), *cfg)) {
            QMessageBox::information(this, "Valid expression", "Expression is valid!");
            runtTM = true;
        } else
            notValidated();
    }

    // If the expression is valid, run the Turing machine
    // Save the result to a file and open the OutputViewer
    //---------------------------------------------------
    if (runtTM) {
        // Calculate the expression with TM
        //---------------------------
        ExpressionCalculator calc(expression_input->text().toStdString());
        calc.calculate();

        // Open the OutputViewer
        //----------------------------
        OutputViewer viewer("../OutputFiles", {"*.html", "*.txt"}, this);
        viewer.exec();
    }
}
