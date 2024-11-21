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
#include "Headers/EarleyParser.h"
#include "Headers/CFG.h"

int main(int argc, char *argv[]) {
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    TransitionFunction tf;

    tf.addTransition("q0", {'1', '_'}, "q0", {'_', '1'}, {LEFT, RIGHT});  // Verwerk het eerste getal
    tf.addTransition("q0", {'+', '_'}, "q1", {'+', '_'}, {LEFT, STAY});   // Ga naar q1 bij de '+'
    tf.addTransition("q1", {'1', '_'}, "q1", {'_', '1'}, {LEFT, RIGHT});  // Verwerk het tweede getal
    tf.addTransition("q1", {'_', '_'}, "q_accept", {'_', '_'}, {STAY, STAY});  // Ga naar accept als alles verwerkt is

    machine.setTransitionFunction(tf);
    machine.getTape(0).setContent("11+11"); // 2 + 2
    machine.getTape(1).setContent("_");

     std::cout << "Initial Tapes:\n";
     machine.printTapes();
    
     if (machine.run()) {
         std::cout << "Machine accepted the input. Result:\n";
     } else {
         std::cout << "Machine rejected the input.\n";
     }
    
     machine.printTapes();
    // /**
    //  * Application
    //  */
    //  QApplication app(argc, argv);
    //  MainWindow turing_tutor;
    //  turing_tutor.show();
    //
    // CFG cfg{"InputFiles/expressionCFG.json"};
    // std::cout << std::boolalpha << parser::EarleyParser::getInstance().parse("4+5", cfg) << std::endl;

    return 0;
}
