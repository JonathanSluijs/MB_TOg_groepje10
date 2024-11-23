//
// Created by cain on 23/11/24.
//
#include <gtest/gtest.h>
#include "../Headers/ExpressionCalculator.h"

// Fixture klasse voor TransitionFunction Tests
class ExpressionCalculatorTests : public ::testing::Test {
protected:
    void SetUp() override {
        // Initiële setup, bijvoorbeeld het toevoegen van enkele basisovergangen.
    }

    void TearDown() override {
        // Eventuele schoonmaakwerkzaamheden.
    }
};

// Test voor het berekenen van een expressie
TEST_F(ExpressionCalculatorTests, CalculateExpression) {
    // Test 1
    ExpressionCalculator expCalc = ExpressionCalculator("2-5*9^2*(3-1)");
    EXPECT_EQ(expCalc.calculate(), -808);

    // Test 2
    ExpressionCalculator expCalc2 = ExpressionCalculator("21+3*4");
    EXPECT_EQ(expCalc2.calculate(), 33);

    // Test 3
    ExpressionCalculator expCalc3 = ExpressionCalculator("2^3");
    EXPECT_EQ(expCalc3.calculate(), 8);

    // Test 4
    ExpressionCalculator expCalc4 = ExpressionCalculator("2^3*2");
    EXPECT_EQ(expCalc4.calculate(), 16);

    // Test 5
    ExpressionCalculator expCalc5 = ExpressionCalculator("2^3*2+10");
    EXPECT_EQ(expCalc5.calculate(), 26);
}
