/*********************************************************************************************
* @file Logger.h
 * @brief Logger class.
 **********************************************************************************************/

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "../libs/nlohmann/json.hpp"

class Logger {
public:
    enum Level {
        INFO,
        DEBUG,
        WARN,
        RUN
    };

    explicit Logger(const std::string &logFileName, const std::string &jsonFileName, bool logToConsole = true);
    ~Logger();

    void log(Level level, const std::string &message);
    void setLogLevel(Level level);
    void setPhase(const std::string &phaseName);

private:
    std::ofstream fileStream;
    std::ofstream jsonFileStream;
    Level minLogLevel = INFO;
    bool logToConsole;
    std::string currentPhase = "GENERAL";
    nlohmann::json logData;
    nlohmann::json phaseLogs;

    std::string getLevelString(Level level) const;
    void finalizeJson();
    std::string getPhaseNumber(const std::string &phaseName);
    void writePhaseLogsToFile(const std::string &filename);


};

#endif //LOGGER_H

