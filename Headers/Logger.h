/*********************************************************************************************
* @file Logger.h
 * @brief Logger class.
 **********************************************************************************************/

#ifndef LOGGER_H
#define LOGGER_H

#include <mutex>
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
    void closeJson();
    std::ofstream fileStream;
    std::ofstream jsonFileStream;
    void finalizeJson();


private:
    std::mutex logMutex;
    Level minLogLevel = INFO;
    bool logToConsole;
    std::string currentPhase = "GENERAL";
    nlohmann::json logData;
    nlohmann::json phaseLogs;

    std::string getLevelString(Level level) const;
    std::string getPhaseNumber(const std::string &phaseName);
    void writePhaseLogsToFile(const std::string &filename);



};

#endif //LOGGER_H

