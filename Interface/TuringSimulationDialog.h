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
#include <QLabel>
#include <QGridLayout>

class CFG;

class TuringSimulationDialog: public QDialog {
    Q_OBJECT

private:

    /**
     * @brief Button to submit the expression
     */
    QPushButton* submit_button = nullptr;

    /**
     * @brief Input field for the expression
     */
    QLineEdit* expression_input = nullptr;

    /**
     * @brief Radio button to select cyk algorithm
     */
    QRadioButton* cyk_algorithm = nullptr;

    /**
     * @brief Radio button to select earley algorithm
     */
    QRadioButton* earley_algorithm = nullptr;

   /**
    * @brief A label with information about the parsing algorithm
    */
    QLabel* parser_info = nullptr;

   /**
    *@brief A label with information about the input
    */
    QLabel* input_info = nullptr;

   /**
    * @brief Layout of the dialog
    */
    QGridLayout* layout = nullptr;

   /**
    * @brief CNF object that defines the grammar for the arithmetic expressions in Chomsky Normal Form
    */
    CFG* cnf = nullptr;

    /**
     * @brief CFG object that defines the grammar for arithmetic expressions
     */
    CFG* cfg = nullptr;



public:

    /**
     * @brief Constructor for the TuringSimulationDialog class.
     * @param CNF_file path to the grammar file in chomsky normal form
     * @param CFG_file path to the grammar file
     * @param parent parent widget
     */
    explicit TuringSimulationDialog(const std::string& CNF_file, const std::string& CFG_file, QWidget* parent = 0);

    /**
     * @brief Destructor for the TuringSimulationDialog class.
     */
    ~TuringSimulationDialog() override;

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
    void limitCharacters() const;

   /**
    * @brief Function that displays a message if the expression is not valid.
    */
    void notValidated();

signals:
private slots:
    /**
    * @brief Submits the expression to be calculated.
    * @brief This function will call the appropriate function to calculate the expression
    * @brief and display the result.
    */
    void submitExpression();
};



#endif //TURINGSIMULATIONDIALOG_H
