

#include "../Headers/CFG.h"


StringSet findExistingRule(const std::string &terminal, const std::map<std::string, StringSet> &productions) {
    StringSet variables;
    for (const auto &rule: productions) {
        if (rule.second.find(terminal) != rule.second.end()) {
            variables.insert(rule.first);
        }
    }
    return variables;
}

StringSet cartesianProduct(const StringSet &set1, const StringSet &set2) {
    StringSet variable_combinations;
    for (const auto &variable1: set1) {
        for (const auto &variable2: set2) {
            variable_combinations.insert(variable1 + " " + variable2);
        }
    }
    return variable_combinations;
}


CFG::CFG() {}

CFG::CFG(std::string filename) {

    // Open input stream
    std::ifstream input_file(filename);

    // Read json file
    json j;
    input_file >> j;

    variables = static_cast<StringSet>(j["Variables"]);
    terminals = static_cast<StringSet>(j["Terminals"]);
    start_symbol = j["Start"];

    for (json::iterator it = j["Productions"].begin(); it != j["Productions"].end(); it++) {
        std::string head = (*it)["head"];
        std::string body;
        for (const std::string symbol: (*it)["body"]) {
            body.empty() ? body += symbol : body += " " + symbol;
        }
        production_rules[head].insert(body);
    }
}

void CFG::print() const {
    std::cout << "V = " << Logger::setToString(variables) << std::endl;
    std::cout << "T = " << Logger::setToString(terminals) << std::endl;
    Logger::printProductions(production_rules);
    std::cout << "S = " << start_symbol << std::endl;
}

void CFG::addVariable(const std::string &variable) {
    variables.insert(variable);
}

void CFG::setTerminals(const StringSet &terminal_list) {
    CFG::terminals = terminal_list;
}

void CFG::setStartSymbol(const std::string &startSymbol) {
    start_symbol = startSymbol;
}

void CFG::addProductionRule(const std::string head, const std::string body) {
    production_rules[head].insert(body);
}


void CFG::accepts(const std::string &input_string) {

    std::vector<std::vector<TableObject>> table;
    AssociationGroup group;

    for (int i = 0; i < input_string.size(); i++) {
        std::vector<TableObject> row;
        for (int j = 0; j < input_string.size() - i; j++) {
            TableObject table_object;
            table_object.setToken(input_string.substr(j, i + 1));
            row.push_back(table_object);
        }
        table.push_back(row);
    }
    // Do the first row
    for (auto &table_object: table[0]) {
        StringSet variables = findExistingRule(table_object.getToken(), production_rules);
        table_object.setVariables(variables);
        group.setAssociation(table_object.getToken(), variables);
    }

    for (int i = 1; i < table.size(); i++) {
        for (auto &table_object: table[i]) {
            StringSet body_group;

            for (const auto &token_split: table_object.getTokenCombination()) {
                StringSet bodies = (cartesianProduct(group.getAssociativeVariables(token_split.first),
                                                     group.getAssociativeVariables(token_split.second)));
                body_group.insert(bodies.begin(), bodies.end());

            }
            StringSet final_variables;
            for (const auto &string: body_group) {
                StringSet variables = findExistingRule(string, production_rules);
                final_variables.insert(variables.begin(), variables.end());
            }
            group.setAssociation(table_object.getToken(), final_variables);
            table_object.setVariables(final_variables);
        }
    }

    // Print the table
    Logger::printAcceptanceTable(table);

    // Print the acceptance boolean
    std::cout << std::boolalpha;
    std::cout << (table[input_string.size() - 1][0].getVariables().find(start_symbol) !=
                  table[input_string.size() - 1][0].getVariables().end()) << std::endl;

}

const StringSet &TableObject::getVariables() const {
    return variables;
}

void TableObject::setVariables(const StringSet &vars) {
    TableObject::variables = vars;
}

const std::string &TableObject::getToken() const {
    return token;
}

void TableObject::setToken(std::string Token) {
    TableObject::token = std::move(Token);
}

std::set<std::pair<std::string, std::string>> TableObject::getTokenCombination() const {
    std::set<std::pair<std::string, std::string>> token_combinations;
    if (token.size() == 1) {
        token_combinations.insert(std::make_pair(token, ""));
    } else {
        for (int i = 0; i < token.size() - 1; i++) {
            token_combinations.insert(
                    std::pair<std::string, std::string>{token.substr(0, i + 1), token.substr(i + 1, token.size())});
        }
    }
    return token_combinations;
}

void AssociationGroup::setAssociation(const std::string &string, const StringSet &variables) {
    associations[string] = variables;
}

StringSet &AssociationGroup::getAssociativeVariables(const std::string &string) {
    return associations[string];
}
