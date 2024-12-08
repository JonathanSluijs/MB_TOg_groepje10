/***********************************************************************************************
 * @file main.cpp
 * @brief This file contains the main function which is the entry point of the program
 * @brief You can change the resolution of the MainWindow by adding width and height to the constructor
 * @warning DO NOT CHANGE THIS FILE BESIDES THE RESOLUTION
 * @version 1.0
 * @date 2024-11-17
 **********************************************************************************************/

#include "Headers/MultiTapeTuringMachine.h"
#include <QApplication>
#include "Interface/MainWindow.h"
#include "Parsers//EarleyParser.h"
#include "Headers/CFG.h"
#include "Headers/ExpressionCalculator.h"

int main(int argc, char *argv[]) {
    /**
     * Application
     */
     QApplication app(argc, argv);
     MainWindow turing_tutor;
     turing_tutor.show();
     return app.exec();
}
