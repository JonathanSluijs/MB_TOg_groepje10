/*****************************************************************************************
* @file MainWindow.h
* @brief This file contains the declaration of the MainWindow class
* which is responsible for creating the main window of the application.
*****************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    /**
     * @brief Button to go to the math calculator window
     */
    QPushButton* math_calculator;

    /**
     * @brief Button to go to the turing machine simulator window
     */
    QPushButton* turing_simulator;

public:
    /**
    * @brief Constructor for the MainWindow class.
    * @param width width of the main window (default 1920)
    * @param height height of the main window (default 1080)
     */
    explicit MainWindow(QWidget *parent = 0, int width = 1920, int height = 1080);

    /**
    * @brief Destructor for the MainWindow class.
*   */
    ~MainWindow() override = default;

private:
    /**
    * @brief Creates the graphics for the main window.
    */
    void createGraphics();

    /**
    * @brief Creates the events for the main window.
    */
    void createEvents() const;

signals:
private slots:
    /**
     * @brief Goes to the window for math calculation
     */
    void toCalculator();

    /**
    * @brief Goes to the window for turing machine visualization
    */
    void toTMSimulator();
};

#endif //MAINWINDOW_H
