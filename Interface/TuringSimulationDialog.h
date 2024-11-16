//
// Created by emir on 11/16/24.
//

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
