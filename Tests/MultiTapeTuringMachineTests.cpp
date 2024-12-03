#include <gtest/gtest.h>
#include "../Headers/MultiTapeTuringMachine.h"
#include "../Headers/TransitionFunction.h"
#include "../Headers/Tape.h"
#include "../Headers/Utils.h"


class MultiTapeTuringMachineTests : public ::testing::Test {
protected:
    
    void SetUp() override {
        
    }

    
    void TearDown() override {
        
    }
};


TEST_F(MultiTapeTuringMachineTests, TapeReadWriteMove) {
    Tape tape;

    
    tape.setContent("101");

    
    EXPECT_EQ(tape.read(), '1');

    
    tape.write('0');
    EXPECT_EQ(tape.read(), '0');

    
    tape.move(Direction::RIGHT);
    EXPECT_EQ(tape.read(), '0');

    
    tape.move(Direction::LEFT);
    EXPECT_EQ(tape.read(), '0');
}


TEST_F(MultiTapeTuringMachineTests, AddAndGetTransition) {
    TransitionFunction tf;

    
    std::string currentState = "q0";
    std::vector<char> readSymbols = {'1'};
    std::string nextState = "q1";
    std::vector<char> writeSymbols = {'0'};
    std::vector<Direction> movements = {Direction::RIGHT};

    
    tf.addTransition(currentState, readSymbols, nextState, writeSymbols, movements);

    
    EXPECT_TRUE(tf.hasTransition(currentState, readSymbols));

    
    auto [returnedNextState, returnedWriteSymbols, returnedMovements] = tf.getTransition(currentState, readSymbols);

    EXPECT_EQ(returnedNextState, nextState);
    EXPECT_EQ(returnedWriteSymbols, writeSymbols);
    EXPECT_EQ(returnedMovements, movements);
}


TEST_F(MultiTapeTuringMachineTests, AdditionOperation) {
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/additionMTM.json");


    machine.setTransitionFunction(tf);

    
    machine.getTape(0).setContent("11111+111111");
    machine.getTape(1).setContent("_");

    
    bool result = machine.run();

    
    EXPECT_TRUE(result);

    
    EXPECT_EQ(machine.getTape(1).readAll(), "11111111111_");
}

TEST_F(MultiTapeTuringMachineTests, EmptyInputOperationAddition) {
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/additionMTM.json");
    machine.setTransitionFunction(tf);

    
    machine.getTape(0).setContent("_");
    machine.getTape(1).setContent("_");

    
    bool result = machine.run();

    
    EXPECT_FALSE(result);
}

TEST_F(MultiTapeTuringMachineTests, SubtractionSimpleAccept) {
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/subtractionMTM.json");
    machine.setTransitionFunction(tf);

    
    machine.getTape(0).setContent("11-11");
    machine.getTape(1).setContent("_");

    
    bool result = machine.run();

    
    EXPECT_TRUE(result);

    
    EXPECT_EQ(machine.getTape(1).readAll(), "____");
}

TEST_F(MultiTapeTuringMachineTests, SubtractionRemainderAccept) {
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/subtractionMTM.json");
    machine.setTransitionFunction(tf);

    
    machine.getTape(0).setContent("11-1");
    machine.getTape(1).setContent("_");

    
    bool result = machine.run();

    
    EXPECT_TRUE(result);

    
    EXPECT_EQ(machine.getTape(1).readAll(), "1__");
}

TEST_F(MultiTapeTuringMachineTests, SubtractionRejectTooLargeSecondOperand) {
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/subtractionMTM.json");
    machine.setTransitionFunction(tf);

    
    machine.getTape(0).setContent("11-111");
    machine.getTape(1).setContent("_");

    
    bool result = machine.run();

    
    EXPECT_FALSE(result);

    
    EXPECT_EQ(machine.getTape(1).readAll(), "1___");
}

TEST_F(MultiTapeTuringMachineTests, SubtractionEmptyInputReject) {
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/subtractionMTM.json");
    machine.setTransitionFunction(tf);

    
    machine.getTape(0).setContent("_");
    machine.getTape(1).setContent("_");

    
    bool result = machine.run();

    
    EXPECT_FALSE(result);
}

TEST_F(MultiTapeTuringMachineTests, DivisionMultipleTapesExactDivision) {
    MultiTapeTuringMachine machine(4, "q0", "q_accept", "q_reject");

    
    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/divisionMTM.json");
    machine.setTransitionFunction(tf);

    
    machine.getTape(0).setContent("11111111111");  
    machine.getTape(1).setContent("11111111111");  
    machine.getTape(2).setContent("_");           
    machine.getTape(3).setContent("_");           

    
    bool result = machine.run();

    
    EXPECT_TRUE(result);

    
    EXPECT_EQ(machine.getTape(2).readAll(), "_____________");
    EXPECT_EQ(machine.getTape(3).readAll(), "1_");  
}

TEST_F(MultiTapeTuringMachineTests, DivisionMultipleTapesWithRemainder) {
    MultiTapeTuringMachine machine(4, "q0", "q_accept", "q_reject");

    
    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/divisionMTM.json");
    machine.setTransitionFunction(tf);

    
    machine.getTape(0).setContent("1111111");     
    machine.getTape(1).setContent("1111");        
    machine.getTape(2).setContent("_");           
    machine.getTape(3).setContent("_");           

    
    bool result = machine.run();

    
    EXPECT_TRUE(result);

    
    EXPECT_EQ(machine.getTape(2).readAll(), "111___");
    EXPECT_EQ(machine.getTape(3).readAll(), "1_");   
}

// TEST_F(MultiTapeTuringMachineTests, DivisionMultipleTapesZeroDivisorReject) {
//     MultiTapeTuringMachine machine(4, "q0", "q_accept", "q_reject");
//
//
//     TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/divisionMTM.json");
//     machine.setTransitionFunction(tf);
//
//
//     machine.getTape(0).setContent("1111111");
//     machine.getTape(1).setContent("_");
//     machine.getTape(2).setContent("_");
//     machine.getTape(3).setContent("_");
//
//
//     bool result = machine.run();
//
//
//     EXPECT_FALSE(result);
//
//
//     EXPECT_EQ(machine.getTape(2).readAll(), "___");
//     EXPECT_EQ(machine.getTape(3).readAll(), "___");
// }

TEST_F(MultiTapeTuringMachineTests, DivisionMultipleTapesExactLargeValues) {
    MultiTapeTuringMachine machine(4, "q0", "q_accept", "q_reject");

    
    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/divisionMTM.json");
    machine.setTransitionFunction(tf);

    
    machine.getTape(0).setContent("1111111111111111");  
    machine.getTape(1).setContent("1111");              
    machine.getTape(2).setContent("_");                 
    machine.getTape(3).setContent("_");                 

    
    bool result = machine.run();

    
    EXPECT_TRUE(result);

    
    EXPECT_EQ(machine.getTape(2).readAll(), "_________");
    EXPECT_EQ(machine.getTape(3).readAll(), "1111_");   
}

// TEST_F(MultiTapeTuringMachineTests, DivisionMultipleTapesEmptyInputReject) {
//     MultiTapeTuringMachine machine(4, "q0", "q_accept", "q_reject");
//
//
//     TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/divisionMTM.json");
//     machine.setTransitionFunction(tf);
//
//
//     machine.getTape(0).setContent("_");
//     machine.getTape(1).setContent("_");
//     machine.getTape(2).setContent("_");
//     machine.getTape(3).setContent("_");
//
//
//     bool result = machine.run();
//
//
//     EXPECT_FALSE(result);
//
//
//     EXPECT_EQ(machine.getTape(2).readAll(), "___");
//     EXPECT_EQ(machine.getTape(3).readAll(), "___");
// }



