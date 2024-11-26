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
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    // TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/additionMTM.json");
    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/subtractionMTM.json");


    machine.setTransitionFunction(tf);

    // machine.getTape(0).setContent("1111111+111111");

    machine.getTape(0).setContent("-"); // 11-11 accept, 11-1 accept, 11-111 reject \\TODO EMIR dit kan toch nooit voorkomen door de earley parser?
    machine.getTape(1).setContent("_");

     std::cout << "Initial Tapes:\n";
     machine.printTapes();

     if (machine.run()) {
         std::cout << "Machine accepted the input. Result:\n";
     } else {
         std::cout << "Machine rejected the input.\n";
     }

     machine.printTapes();

     // ExpressionCalculator calc("2-5*9^2*(3-1)"); // should be -808
     // std::cout << calc.calculate() << std::endl;


    /**
     * Application
     */
    // QApplication app(argc, argv);
    // MainWindow turing_tutor;
    // turing_tutor.show();
    // return app.exec();
}
