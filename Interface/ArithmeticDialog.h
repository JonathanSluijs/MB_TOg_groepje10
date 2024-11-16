//
// Created by emir on 11/16/24.
//

#ifndef ARITHMETICDIALOG_H
#define ARITHMETICDIALOG_H

#include <QDialog>

class ArithmeticDialog: public QDialog {
    Q_OBJECT
public:

    /**
     * @brief Constructor for the ArithmeticDialog class.
     * @param parent parent widget
     */
    ArithmeticDialog(QWidget* parent = 0);

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


signals:
private slots:

};



#endif //ARITHMETICDIALOG_H
