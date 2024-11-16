/*****************************************************************************************
* @file TuringSimulationDialog
* @brief This file contains the declaration of the TuringSimulationDialog class
* which is responsible for submitting, validating expressions with parsing algorithms 
* and turing simulation of the calculation.
*****************************************************************************************/

#ifndef TURINGSIMULATIONDIALOG_H
#define TURINGSIMULATIONDIALOG_H

#include <QDialog>

class TuringSimulationDialog: public QDialog {
    Q_OBJECT
public:

    /**
     * @brief Constructor for the TuringSimulationDialog class.
     * @param parent parent widget
     */
    TuringSimulationDialog(QWidget* parent = 0);

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
};



#endif //TURINGSIMULATIONDIALOG_H
