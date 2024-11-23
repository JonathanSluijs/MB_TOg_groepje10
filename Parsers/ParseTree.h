//
// Created by emir on 11/22/24.
//

#ifndef PARSETREE_H
#define PARSETREE_H

#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace parser{

class ParseTree{

    /**
     * @brief Vector with the nodes (subtrees) of a node (= subtree root)
     */
    std::vector<std::unique_ptr<ParseTree>> subtrees;

    /**
     * @brief Content of the root of the current subtree
     */
    std::string content_;

public:

    /**
    * @brief Constructor of the ParseTree
    * @param func a function that initializes the parse tree for a specific parser
    */
    ParseTree() = default;

    /**
     * @brief Default destructor of the ParseTree
     */
    ~ParseTree() = default;


};
}

#endif //PARSETREE_H
