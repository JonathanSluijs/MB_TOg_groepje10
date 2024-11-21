//
// Created by Mathis De Herdt on 21/11/2024.
//
#include <gtest/gtest.h>
#include "../Headers/TransitionFunction.h"
#include "../Headers/Utils.h"

// Fixture klasse voor TransitionFunction Tests
class TransitionFunctionTests : public ::testing::Test {
protected:
    TransitionFunction tf;

    void SetUp() override {
        // Initiële setup, bijvoorbeeld het toevoegen van enkele basisovergangen.
    }

    void TearDown() override {
        // Eventuele schoonmaakwerkzaamheden.
    }
};

// Test voor het toevoegen en ophalen van een overgang
TEST_F(TransitionFunctionTests, AddAndGetTransition) {
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

// Test voor het ophalen van een niet-bestaande overgang
TEST_F(TransitionFunctionTests, GetNonExistentTransition) {
    std::string currentState = "q2";
    std::vector<char> readSymbols = {'0'};

    EXPECT_FALSE(tf.hasTransition(currentState, readSymbols));
}

