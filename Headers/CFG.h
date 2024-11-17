

#ifndef CFG_CFG_H
#define CFG_CFG_H

#include <string>
#include <set>
#include <sstream>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "json.hpp"
#include "Logger.h"

using StringSet = std::set<std::string>;
using json = nlohmann::json;


class TableObject {

private:

    StringSet variables;

    std::string token;

public:

    TableObject() = default;

    [[nodiscard]] const StringSet &getVariables() const;

    void setVariables(const StringSet &vars);

    [[nodiscard]] const std::string &getToken() const;

    void setToken(std::string token);

    [[nodiscard]] std::set<std::pair<std::string, std::string>> getTokenCombination() const;

};

class AssociationGroup {

private:

    std::map<std::string, StringSet> associations;
public:

    AssociationGroup() = default;

    void setAssociation(const std::string &string, const StringSet &variables);

    StringSet &getAssociativeVariables(const std::string &string);

};

/**
 * Calculates the cartesian product of two sets with variables and returns set with variable strings
 * @param set1 variable set 1
 * @param set2 variable set 2
 * @return set with concatenation of two variables for later use purposes
 */
StringSet cartesianProduct(const StringSet &set1, const StringSet &set2);

/**
 * Finds the production rule heads for a given map of production rules and a body
 * @param terminal the body (can be a terminal or variables)
 * @param productions the productions of the CFG
 * @return set of string with variables (production heads)
 */
StringSet findExistingRule(const std::string &terminal, const std::map<std::string, StringSet> &productions);


class CFG {

private:

    /**
     * Variables of the CFG
     */
    StringSet variables;

    /**
     * Terminals of the CFG
     */
    StringSet terminals;

    /**
     * Production rules of the CFG
     */
    std::map<std::string, StringSet> production_rules;

    /**
     * Start symbol of the CFG
     */
    std::string start_symbol;

public:

    /**
    * Empty base constructor of the CFG class
     */
    CFG();

    /**
     * Constructor of the CFG class
     * @param filename json file that is read
     */
    CFG(std::string filename);

    /**
     * Prints information about the CFG
     */
    void print() const;

    /**
     * Function that runs the CYK algorithm
     * @param input_string string that has to be checked
     */
    void accepts(const std::string &input_string);

    /**
     * Adds a variable to the set of variables
     * @param variable the variable to add
     */
    void addVariable(const std::string &variable);

    /**
     * Sets the terminals of the CFG
     * @param terminal_list the terminals to add
     */
    void setTerminals(const StringSet &terminal_list);

    /**
     * Sets the start symbol of the CFG
     * @param startSymbol new start symbol
     */
    void setStartSymbol(const std::string &startSymbol);

    /**
     * Adds a production rule to the productions
     * @param head the head of the production
     * @param body the body of the production
     */
    void addProductionRule(std::string head, std::string body);
};


#endif //CFG_CFG_H
