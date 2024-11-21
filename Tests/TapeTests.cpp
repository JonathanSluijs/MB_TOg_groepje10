//
// Created by Mathis De Herdt on 21/11/2024.
//
#include <gtest/gtest.h>
#include "../Headers/Tape.h"
#include "../Headers/Utils.h"

// Fixture klasse voor Tape Tests
class TapeTests : public ::testing::Test {
protected:
    Tape tape;

    void SetUp() override {
        tape.setContent("101");
    }

    void TearDown() override {
        // Eventuele schoonmaakwerkzaamheden.
    }
};

// Test voor het lezen van de tape
TEST_F(TapeTests, ReadSymbol) {
    EXPECT_EQ(tape.read(), '1');
}

// Test voor het schrijven naar de tape
TEST_F(TapeTests, WriteSymbol) {
    tape.write('0');
    EXPECT_EQ(tape.read(), '0');
}

// Test voor het bewegen van de tape naar rechts
TEST_F(TapeTests, MoveRight) {
    tape.move(Direction::RIGHT);
    EXPECT_EQ(tape.read(), '0');
}

// Test voor het bewegen van de tape naar links
TEST_F(TapeTests, MoveLeft) {
    tape.move(Direction::RIGHT);
    tape.move(Direction::LEFT);
    EXPECT_EQ(tape.read(), '1');
}

// Test voor het lezen van de volledige inhoud van de tape
TEST_F(TapeTests, ReadAllContent) {
    EXPECT_EQ(tape.readAll(), "101");
}

// Test voor het zetten van de inhoud van de tape
TEST_F(TapeTests, SetContent) {
    tape.setContent("110");
    EXPECT_EQ(tape.readAll(), "110");
    EXPECT_EQ(tape.read(), '1');
}
