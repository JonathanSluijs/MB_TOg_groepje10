/**************************************************************************************************
 * @file EarleyParser.h
 * @brief Singleton class for EarleyParser
 * @brief Header file for EarleyParser class which is used to parse a given string using
 * Earley's parsing algorithm (for more information https://en.wikipedia.org/wiki/Earley_parser)
 * @see EarleyParser.cpp
 **************************************************************************************************/

#ifndef EARLEYPARSER_H
#define EARLEYPARSER_H

#include <string>

class CFG;

namespace parser {


class EarleyParser {
private:
 /**
 * @brief Default constructor for EarleyParser class
 */
 EarleyParser() = default;

 /**
 * @brief Default destructor for EarleyParser class
 */
 ~EarleyParser() = default;

public:
 /**
  * @brief Deleted copy constructor for EarleyParser class
  */
 EarleyParser(const EarleyParser &) = delete;

 /**
 * @brief Deleted copy assignment operator for EarleyParser class
 */
 EarleyParser &operator=(const EarleyParser &) = delete;

 /**
  * @brief Returns the instance of EarleyParser class
  * @brief If instance does not exist, creates a new  unique instance
  */
 static EarleyParser &getInstance();

 /**
 * @brief Parses the given input string using Earley's parsing algorithm
 * @param input The string to be parsed
 * @param cfg The CFG object to be used for parsing
 */
 static void parse(const std::string &input, const CFG &cfg);
};
}


#endif //EARLEYPARSER_H
