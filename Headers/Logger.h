//
// Created by 2005e on 25/10/2024.
//

#ifndef CFG_LOGGER_H
#define CFG_LOGGER_H

#include <iostream>
#include <set>
#include <vector>
#include <map>

using StringSet = std::set<std::string>;
class CFG;
class TableObject;
class AssociationGroup;

class Logger {
public:

    /**
    * Function that converts a set to a string representation
    */
    static std::string setToString(const StringSet &string_set);

    /**
    * Splits a string on spaces
    * @param str the string input that has to be split
    * @return a vector of strings
    */
    static std::vector<std::string> splitString(const std::string &str);

    /**
    * Prints the resulting table of the CYK algorithm
    * @param table the table data structure representing the table
    */
    static void printAcceptanceTable(const std::vector<std::vector<TableObject>> &table);

    /**
    * Function that prints the productions of a CFG
    */
    static void printProductions(const std::map<std::string, StringSet> &productions);

private:

    /**
     * Function that generates a string of spaces or underlines
     * @param count # of spaces
     * @param underlining if true, the spaces will be replaced by underlines
     * @return a string of spaces or underlines
     */
    static std::string generateSpaces(int count, bool underlining);


};


#endif //CFG_LOGGER_H

