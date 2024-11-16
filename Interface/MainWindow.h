/*****************************************************************************************
* @file MainWindow.h
* @brief This file contains the declaration of the MainWindow class
* which is responsible for creating the main window of the application.
*****************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <memory>

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    /**
     * @brief Button to go to the math calculator window
     */
    std::unique_ptr<QPushButton> math_calculator;

    /**
     * @brief Button to go to the turing machine simulator window
     */
    std::unique_ptr<QPushButton> turing_simulator;

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
    ~MainWindow() override;

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
    void toElementaryStudent();

    /**
    * @brief Goes to the window for turing machine visualization
    */
    void toCSStudent();
};

#endif //MAINWINDOW_H
