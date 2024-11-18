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

class CFG;
class EarlyItem;

typedef std::vector<std::set<EarlyItem > > StateSets;

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

  /**
   * @brief Predicts the next set of states based on the current set of states
   */
  void predict(StateSets &state_sets, const CFG &cfg, unsigned int set_number);

  /**
   * @brief Scans the current character and adds the next state to the state set
   */
  void scan(StateSets &state_sets, const CFG &cfg, unsigned int set_number, const char &cur_char);

  /**
   * @brief Completes the current set of states
   */
  void complete(StateSets &state_sets, const CFG &cfg, unsigned int set_number);

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
  static bool parse(const std::string &input, const CFG &cfg);
 };


 class EarlyItem {
 private:

  /**
   * @brief The position of the dot in the production
   */
  int dot_position = 0;

  /**
   * @brief The production rule of the item
   */
  std::vector<std::string> production = {};

  /**
   * @brief The starting point of the item
   */
  int starting_point = 0;

 public:
  /**
   * @brief Default constructor for EarlyItem class
   */
  EarlyItem() = default;

  /**
   * @brief Default destructor for EarlyItem class
   */
  ~EarlyItem() = default;

  /**
   * @brief Returns the position of the dot in the production
   */
  [[nodiscard]] int getDotPosition() const;

  /**
   * @brief Sets the position of the dot in the production
   */
  void setDotPosition(int dot_position);

  /**
   * @brief Returns the production rule of the item
   */
  [[nodiscard]] const std::vector<std::string> & getProduction() const;

  /**
  * @brief Sets the production rule of the item
  */
  void setProduction(const std::vector<std::string> &production);

  /**
   * @brief Returns the starting point of the item
   */
  [[nodiscard]] int getStartingPoint() const;

  /**
   * @brief Sets the starting point of the item
   */
  void setStartingPoint(int starting_point);
 };
}


#endif //EARLEYPARSER_H
