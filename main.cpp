//
// Created by Jonat on 01/11/2024.
//

#include "Headers/MultiTapeTuringMachine.h"
#include <QApplication>
#include "Interface/MainWindow.h"

int main(int argc, char *argv[]) {
    // MultiTapeTuringMachine machine(3, "q0", "q_accept", "q_reject");
    //
    // TransitionFunction tf;
    //
    // // Add all transitions for binary addition
    // tf.addTransition("q0", {'0', '0', '_'}, "q0", {'0', '0', '0'}, {LEFT, LEFT, LEFT});
    // tf.addTransition("q0", {'0', '1', '_'}, "q0", {'0', '1', '1'}, {LEFT, LEFT, LEFT});
    // tf.addTransition("q0", {'1', '0', '_'}, "q0", {'1', '0', '1'}, {LEFT, LEFT, LEFT});
    // tf.addTransition("q0", {'1', '1', '_'}, "q1", {'1', '1', '0'}, {LEFT, LEFT, LEFT});
    // tf.addTransition("q1", {'0', '0', '_'}, "q0", {'0', '0', '1'}, {LEFT, LEFT, LEFT});
    // tf.addTransition("q1", {'0', '1', '_'}, "q1", {'0', '1', '0'}, {LEFT, LEFT, LEFT});
    // tf.addTransition("q1", {'1', '0', '_'}, "q1", {'1', '0', '0'}, {LEFT, LEFT, LEFT});
    // tf.addTransition("q1", {'1', '1', '_'}, "q1", {'1', '1', '1'}, {LEFT, LEFT, LEFT});
    // tf.addTransition("q0", {'_', '_', '_'}, "q_accept", {'_', '_', '_'}, {STAY, STAY, STAY});
    // tf.addTransition("q1", {'_', '_', '_'}, "q_accept", {'_', '_', '1'}, {STAY, STAY, STAY});
    //
    // machine.setTransitionFunction(tf);
    //
    // // Initialize tapes with binary numbers
    // machine.getTape(0).setContent("1101");      // Binary for 13
    // machine.getTape(1).setContent("1010");      // Binary for 10
    // machine.getTape(2).setContent("_");         // Result tape starts empty
    //
    // std::cout << "Initial Tapes:\n";
    // machine.printTapes();
    //
    // if (machine.run()) {
    //     std::cout << "Machine accepted the input. Result:\n";
    // } else {
    //     std::cout << "Machine rejected the input.\n";
    // }
    //
    // machine.printTapes();
    QApplication app(argc, argv);
    MainWindow turing_tutor;
    turing_tutor.show();
    return app.exec();
}
