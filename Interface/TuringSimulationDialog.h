/*****************************************************************************************
* @file TuringSimulationDialog.h
* @brief This file contains the declaration of the TuringSimulationDialog class
* which is responsible for submitting, validating expressions with parsing algorithms 
* and turing simulation of the calculation.
*****************************************************************************************/

#ifndef TURINGSIMULATIONDIALOG_H
#define TURINGSIMULATIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>

class TuringSimulationDialog: public QDialog {
    Q_OBJECT

private:

    /**
     * @brief Button to submit the expression
     */
    QPushButton* submit_button;

    /**
     * @brief Input field for the expression
     */
    QLineEdit* expression_input;

    /**
     * @brief Radio button to select cyk algorithm
     */
    QRadioButton* cyk_algorithm;

    /**
     * @brief Radio button to select earley algorithm
     */
    QRadioButton* earley_algorithm;

public:

    /**
     * @brief Constructor for the TuringSimulationDialog class.
     * @param parent parent widget
     */
    TuringSimulationDialog(QWidget* parent = 0);

    /**
     * @brief Destructor for the TuringSimulationDialog class.
     */
    ~TuringSimulationDialog() override = default;

private:

    /**
     * @brief Creates the graphics for the turing simulation dialog.
     */
    void createGraphics();

    /**
     * @brief Creates the events for the turing simulation dialog.
     */
    void createEvents() const;

    /**
    * @brief Function that limits the characters
    * that can be entered in the expression input field.
    */
    void limitCharacters();

    /**
    * @brief Submits the expression to be calculated.
    * @brief This function will call the appropriate function to calculate the expression
    * @brief and display the result.
    */
    void submitExpression();
};



#endif //TURINGSIMULATIONDIALOG_H
