/*****************************************************************************************
 * @file CFG.h
 * @brief Class that represents a Context-Free Grammar
 * @see CFG.cpp
 ****************************************************************************************/

#ifndef CFG_H
#define CFG_H

#include <vector>
#include <string>
#include <map>

class CFG {
    /**
    * @brief The variables of the CFG
    */
    std::vector<std::string> variables;

    /**
    * @brief The terminals of the CFG
    */
    std::vector<std::string> terminals;

    /**
    * @brief The productions of the CFG
    */
    std::map<std::string, std::vector<std::vector<std::string> > > productions;

    /**
    * @brief The start symbol of the CFG
    */
    std::string start;

public:
    /**
    * @brief Constructor of the CFG class
    * @param filename The name of the file to read the CFG from (JSON format)
    */
    CFG(const std::string &filename);

    /**
    * @brief Prints the CFG
    */
    void print() const;

    /**
    * @brief Sorts the productions
    */
    void sortProductions();

    /**
    * @brief Compares two productions
    * @param prod1 The first production
    * @param prod2 The second production
    */
    bool compareProductions(const std::vector<std::string> &prod1, const std::vector<std::string> &prod2);

    /**
     * @brief Function that checks if a given string is a terminal
     */
    [[nodiscard]] bool isTerminal(const std::string &str) const;

    /**
     * @brief Function that checks if a given string is a variable
     */
    [[nodiscard]] bool isVariable(const std::string &str) const;

    /**
    * @brief Getter for the variables
    */
    [[nodiscard]] std::vector<std::string> getVariables() const;

    /**
    * @brief Getter for the terminals
    */
    [[nodiscard]] std::vector<std::string> getTerminals() const;

    /**
    * @brief Getter for the productions
    */
    [[nodiscard]] std::map<std::string, std::vector<std::vector<std::string> > > getProductions() const;

    /**
    * @brief Getter for the start symbol
    */
    [[nodiscard]] const std::string& getStartSymbol() const;
};


#endif //CFG_H
