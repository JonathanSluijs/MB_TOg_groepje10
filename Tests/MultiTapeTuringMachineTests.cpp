#include <gtest/gtest.h>
#include "../Headers/MultiTapeTuringMachine.h"
#include "../Headers/TransitionFunction.h"
#include "../Headers/Tape.h"
#include "../Headers/Utils.h"

// Fixture klasse voor de MultiTapeTuringMachine Tests
class MultiTapeTuringMachineTests : public ::testing::Test {
protected:
    // SetUp die vooraf aan elke test wordt uitgevoerd
    void SetUp() override {
        // Je kan hier eventueel resources alloceren of initialisatie uitvoeren
    }

    // TearDown die na elke test wordt uitgevoerd
    void TearDown() override {
        // Je kan hier resources vrijgeven indien nodig
    }
};

// Test voor de Tape functionaliteit
TEST_F(MultiTapeTuringMachineTests, TapeReadWriteMove) {
    Tape tape;

    // Initiele content toevoegen
    tape.setContent("101");

    // Test leesfunctionaliteit
    EXPECT_EQ(tape.read(), '1');

    // Schrijf een nieuwe waarde
    tape.write('0');
    EXPECT_EQ(tape.read(), '0');

    // Beweeg naar rechts en controleer de volgende waarde
    tape.move(Direction::RIGHT);
    EXPECT_EQ(tape.read(), '0');

    // Beweeg naar links en controleer de nieuwe waarde
    tape.move(Direction::LEFT);
    EXPECT_EQ(tape.read(), '0');
}

// Test voor TransitionFunction functionaliteit
TEST_F(MultiTapeTuringMachineTests, AddAndGetTransition) {
    TransitionFunction tf;

    // Definieer een overgang
    std::string currentState = "q0";
    std::vector<char> readSymbols = {'1'};
    std::string nextState = "q1";
    std::vector<char> writeSymbols = {'0'};
    std::vector<Direction> movements = {Direction::RIGHT};

    // Voeg de overgang toe
    tf.addTransition(currentState, readSymbols, nextState, writeSymbols, movements);

    // Controleer of de overgang bestaat
    EXPECT_TRUE(tf.hasTransition(currentState, readSymbols));

    // Haal de overgang op en controleer de waarden
    auto [returnedNextState, returnedWriteSymbols, returnedMovements] = tf.getTransition(currentState, readSymbols);

    EXPECT_EQ(returnedNextState, nextState);
    EXPECT_EQ(returnedWriteSymbols, writeSymbols);
    EXPECT_EQ(returnedMovements, movements);
}

// Test voor MultiTapeTuringMachine functionaliteit
TEST_F(MultiTapeTuringMachineTests, AdditionOperation) {
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/additionMTM.json");


    machine.setTransitionFunction(tf);

    // Stel de beginwaarde van de tape in
    machine.getTape(0).setContent("11111+111111");
    machine.getTape(1).setContent("_");

    // Voer de machine uit
    bool result = machine.run();

    // Controleer of de machine het invoer accepteert
    EXPECT_TRUE(result);

    // Controleer de eindinhoud van de tape
    EXPECT_EQ(machine.getTape(1).readAll(), "11111111111_");
}

TEST_F(MultiTapeTuringMachineTests, EmptyInputOperationAddition) {
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/additionMTM.json");
    machine.setTransitionFunction(tf);

    // Stel een lege tape in als invoer
    machine.getTape(0).setContent("_");
    machine.getTape(1).setContent("_");

    // Voer de machine uit
    bool result = machine.run();

    // Verwacht dat de machine de invoer afwijst
    EXPECT_FALSE(result);
}

TEST_F(MultiTapeTuringMachineTests, SubtractionSimpleAccept) {
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/subtractionMTM.json");
    machine.setTransitionFunction(tf);

    // Stel de beginwaarde van de tape in
    machine.getTape(0).setContent("11-11");
    machine.getTape(1).setContent("_");

    // Voer de machine uit
    bool result = machine.run();

    // Controleer of de machine het invoer accepteert
    EXPECT_TRUE(result);

    // Controleer de eindinhoud van de tweede tape
    EXPECT_EQ(machine.getTape(1).readAll(), "____");
}

TEST_F(MultiTapeTuringMachineTests, SubtractionRemainderAccept) {
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/subtractionMTM.json");
    machine.setTransitionFunction(tf);

    // Stel de beginwaarde van de tape in
    machine.getTape(0).setContent("11-1");
    machine.getTape(1).setContent("_");

    // Voer de machine uit
    bool result = machine.run();

    // Controleer of de machine het invoer accepteert
    EXPECT_TRUE(result);

    // Controleer de eindinhoud van de tweede tape
    EXPECT_EQ(machine.getTape(1).readAll(), "1__");
}

TEST_F(MultiTapeTuringMachineTests, SubtractionRejectTooLargeSecondOperand) {
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/subtractionMTM.json");
    machine.setTransitionFunction(tf);

    // Stel de beginwaarde van de tape in
    machine.getTape(0).setContent("11-111");
    machine.getTape(1).setContent("_");

    // Voer de machine uit
    bool result = machine.run();

    // Controleer of de machine de invoer afwijst
    EXPECT_FALSE(result);

    // Controleer de eindinhoud van de tweede tape
    EXPECT_EQ(machine.getTape(1).readAll(), "1___");
}

TEST_F(MultiTapeTuringMachineTests, SubtractionEmptyInputReject) {
    MultiTapeTuringMachine machine(2, "q0", "q_accept", "q_reject");

    TransitionFunction tf = parseTransitionFile("../InputFiles/TransitionFiles/subtractionMTM.json");
    machine.setTransitionFunction(tf);

    // Stel een lege tape in als invoer
    machine.getTape(0).setContent("_");
    machine.getTape(1).setContent("_");

    // Voer de machine uit
    bool result = machine.run();

    // Controleer of de machine de invoer afwijst
    EXPECT_FALSE(result);
}





