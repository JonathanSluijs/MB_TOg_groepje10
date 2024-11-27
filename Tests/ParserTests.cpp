//
// Created by Mathis De Herdt on 27/11/2024.
//
#include <gtest/gtest.h>
#include "../Parsers/EarleyParser.h"
#include "../Parsers/ParseTree.h"
#include "../Parsers/CYKParser.h"
#include "../Headers/CFG.h"


class CFGTests : public ::testing::Test {
protected:
    CFG cfg = CFG("../Tests/TestInputFiles/ExampleTestCFG_1.json");
};

TEST_F(CFGTests, LoadVariables) {
    auto variables = cfg.getVariables();
    EXPECT_FALSE(variables.empty());
    EXPECT_EQ(variables.front(), "A"); 
}

TEST_F(CFGTests, LoadTerminals) {
    auto terminals = cfg.getTerminals();
    EXPECT_FALSE(terminals.empty());
    EXPECT_EQ(terminals.front(), "a");  
}

TEST_F(CFGTests, LoadProductions) {
    auto productions = cfg.getProductions();
    EXPECT_FALSE(productions.empty());
    EXPECT_TRUE(productions.count("S") > 0);
}

TEST_F(CFGTests, ProductionContent) {
    auto productions = cfg.getProductions();
    EXPECT_FALSE(productions["S"].empty());
    EXPECT_EQ(productions["H1"].front().front(), "A"); 
}

TEST_F(CFGTests, StartSymbol) {
    EXPECT_EQ(cfg.getStartSymbol(), "S");
}

TEST_F(CFGTests, IsTerminalCheck) {
    EXPECT_TRUE(cfg.isTerminal("a"));
    EXPECT_FALSE(cfg.isTerminal("S"));
}

TEST_F(CFGTests, IsVariableCheck) {
    EXPECT_TRUE(cfg.isVariable("S"));
    EXPECT_FALSE(cfg.isVariable("a"));
}




class CYKParserTests : public ::testing::Test {
protected:
    parser::CYKParser &parser = parser::CYKParser::getInstance();
    CFG cfg = CFG("../Tests/TestInputFiles/ExampleTestCFG_2.json");

    void SetUp() override {
        
    }
};

TEST_F(CYKParserTests, SimpleParseAccept) {
    std::string input = "ab";
    EXPECT_TRUE(parser.parse(input, cfg));
}

TEST_F(CYKParserTests, SimpleParseReject) {
    std::string input = "aa";
    EXPECT_FALSE(parser.parse(input, cfg));
}

TEST_F(CYKParserTests, LongInputParseReject) {
    std::string input = "aaabbb";
    EXPECT_FALSE(parser.parse(input, cfg));
}
TEST_F(CYKParserTests, LongInputParseAccept) {
    std::string input = "abab";
    EXPECT_TRUE(parser.parse(input, cfg));
}

TEST_F(CYKParserTests, InvalidCharacterParseReject) {
    std::string input = "abc";
    EXPECT_FALSE(parser.parse(input, cfg));
}

TEST_F(CYKParserTests, EmptyStringReject) {
    std::string input = "";
    EXPECT_THROW(parser.parse(input, cfg), std::invalid_argument);
}

TEST_F(CYKParserTests, BalancedSymbolsAccept) {
    std::string input = "aabb";
    EXPECT_FALSE(parser.parse(input, cfg));
}

TEST_F(CYKParserTests, ImbalancedSymbolsReject) {
    std::string input = "aab";
    EXPECT_FALSE(parser.parse(input, cfg));
}



class EarleyParserTests : public ::testing::Test {
protected:
    parser::EarleyParser &parser = parser::EarleyParser::getInstance();
    CFG cfg = CFG("../Tests/TestInputFiles/ExampleTestCFG_3.json");

    void SetUp() override {
        
    }
};

TEST_F(EarleyParserTests, SimpleParseAccept) {
    std::string input = "ab";
    EXPECT_TRUE(parser.parse(input, cfg));
}

TEST_F(EarleyParserTests, SimpleParseReject) {
    std::string input = "aa";
    EXPECT_FALSE(parser.parse(input, cfg));
}

TEST_F(EarleyParserTests, LongInputParseAccept) {
    std::string input = "aaabbb";
    EXPECT_FALSE(parser.parse(input, cfg));
}

TEST_F(EarleyParserTests, InvalidCharacterParseReject) {
    std::string input = "abc";
    EXPECT_FALSE(parser.parse(input, cfg));
}

TEST_F(EarleyParserTests, EmptyStringReject) {
    std::string input = "";
    EXPECT_FALSE(parser.parse(input, cfg));
}

TEST_F(EarleyParserTests, BalancedSymbolsAccept) {
    std::string input = "aaaab";
    EXPECT_TRUE(parser.parse(input, cfg));
}

TEST_F(EarleyParserTests, ImbalancedSymbolsReject) {
    std::string input = "aab";
    EXPECT_TRUE(parser.parse(input, cfg));
}




