/*****************************************************************************************
* @file ArithmeticDialog.h
* @brief This file contains the declaration of the ArithmeticDialog class
* which is responsible for submitting, validating and calling the calculator.
*****************************************************************************************/
#ifndef ARITHMETICDIALOG_H
#define ARITHMETICDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include "../Headers/CFG.h"

class ArithmeticDialog : public QDialog {
    Q_OBJECT

private:
    /**
     * @brief Button to submit the expression
     */
    QPushButton *submit_button = nullptr;

    /**
     * @brief Input field for the expression
     */
    QLineEdit *expression_input = nullptr;

    /**
     * @brief Lablel with information about the input
     */
    QLabel *input_info = nullptr;

    /**
     * @brief Layout of the dialog
     */
    QGridLayout *layout = nullptr;

  /**
    * @brief CFG object that defines the grammar for the arithmetic expressions
    */
    CFG* cfg = nullptr;

public:
    /**
     * @brief Constructor for the ArithmeticDialog class.
     * @param parent parent widget
     * @param grammar_file path to the grammar file
     */
    explicit ArithmeticDialog(const std::string& grammar_file, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the ArithmeticDialog class.
     */
    ~ArithmeticDialog() override;

private:
    /**
     * @brief Creates the graphics for the arithmetic dialog.
     */
    void createGraphics();

    /**
     * @brief Creates the events for the arithmetic dialog.
     */
    void createEvents() const;

    /**
    * @brief Function that displays a message if the expression is not valid.
    */
    void notValidated();

    /**
    * @brief Function that limits the characters
    * that can be entered in the expression input field.
    */
    void limitCharacters() const;


signals:
private slots:
    /**
    * @brief Submits the expression to be calculated.
    * @brief This function will call the appropriate function to calculate the expression
    * @brief and display the result.
    */
    void submitExpression();
};


#endif //ARITHMETICDIALOG_H
