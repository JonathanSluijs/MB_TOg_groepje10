/**************************************************************************************************
 * @file EarleyParser.h
 * @brief Singleton class for EarleyParser
 * @brief Header file for EarleyParser class which is used to parse a given string using
 * Earley's parsing algorithm (for more information https://en.wikipedia.org/wiki/Earley_parser)
 * @brief The EarlyItem class is also defined here which is used to represent an item in the Earley
 * @see EarleyParser.cpp
 **************************************************************************************************/

#ifndef EARLEYPARSER_H
#define EARLEYPARSER_H

#include <string>
#include <vector>
#include <set>
#include <algorithm>

class CFG;

namespace parser {
 class EarlyItem {
  /**
   * @brief The position of the dot in the production
   */
  unsigned int dot = 0;

  /**
   * @brief The head of the production rule
   */
  std::string head;

  /**
   * @brief The production rule of the item
   */
  std::vector<std::string> body = {};

  /**
   * @brief The starting point of the item
   */
  unsigned int starting_point = 0;

 public:
  /**
   * @brief Default constructor for EarlyItem class
   */
  EarlyItem() = default;

  /**
   * @brief Parameterized constructor for EarlyItem class
   * @param dot The position of the dot in the production
   * @param head The head of the production rule
   * @param body The production rule of the item
   * @param starting_point The prediction point of the item
   */
  EarlyItem(unsigned int dot, const std::string &head, const std::vector<std::string> &body,
            unsigned int starting_point);

  /**
   * @brief Copu constructor for the EarlyItem class
   */

  EarlyItem(const EarlyItem &other);

  /**
   * @brief Default destructor for EarlyItem class
   */
  ~EarlyItem() = default;

  /**
   * @brief Function for comparing two EarlyItem objects
   */
  bool operator==(const EarlyItem &other) const;

  /**
   * @brief Returns the position of the dot in the production
   */
  [[nodiscard]] unsigned int Dot() const;

  /**
   * @brief Returns head of production rule in the item
   */
  [[nodiscard]] const std::string &Head() const;

  /**
   * @brief Returns the production rule of the item
   */
  [[nodiscard]] const std::vector<std::string> &Body() const;

  /**
   * @brief Returns the current symbol of the production body
   */
  [[nodiscard]] const std::string &Current() const;

  /**
   * @brief Returns the starting point of the item
   */
  [[nodiscard]] unsigned int StartPoint() const;

  /**
   * @brief Confirmed success when dot >= body.size()
   */
  [[nodiscard]] bool confirmedSuccess() const;
 };


 class EarleyParser {
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
  bool parse(const std::string &input, const CFG &cfg);
 };

 /**
 * @brief Function to add an EarlyItem to a vector if it does not already exist
 */
 inline bool addUnique(std::vector<EarlyItem> &vec, const EarlyItem &item) {
  // Controleer of het item al in de vector staat
  if (std::find(vec.begin(), vec.end(), item) == vec.end()) {
   vec.push_back(item); // Voeg toe als het niet bestaat
   return true;
  }
  return false;
 }

}


#endif //EARLEYPARSER_H
