/****************************************************************************************
 * @file CYKParser.h
 * @brief Singleton class for CYKParser which is used to parse a given string using the
 * @brief Cocke-Younger-Kasami parsing algorithm (see https://en.wikipedia.org/wiki/CYK_algorithm)
 * @see CYKParser.cpp
 ****************************************************************************************/

#ifndef CYKPARSER_H
#define CYKPARSER_H

#include <string>

class CFG;

namespace parser {
 class CYKParser {
 private:
  /**
  * @brief Default constructor for CYKParser class
  */
  CYKParser() = default;

  /**
  * @brief Default destructor for CYKParser class
  */
  ~CYKParser() = default;

 public:
  /**
   * @brief Deleted copy constructor for CYKParser class
   */
  CYKParser(const CYKParser &) = delete;

  /**
   * @brief Deleted copy assignment operator for CYKParser class
   */
  CYKParser &operator=(const CYKParser &) = delete;

  /**
   * @brief Returns the instance of CYKParser class
   * @brief If instance does not exist, creates a new  unique instance
   */
  static CYKParser &getInstance();

  /**
   * @brief Parses a given string
   * @param input The string to be parsed
   * @param cfg The CFG object to be used for parsing
   */
  bool parse(const std::string &input, const CFG &cfg);
 };
}


#endif //CYKPARSER_H
