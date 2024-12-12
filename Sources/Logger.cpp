/*********************************************************************************************
 * @file Logger.cpp
 * @brief Implementation van vereenvoudigde Logger class.
 **********************************************************************************************/

#include "../Headers/Logger.h"
#include <stdexcept>
#include "../libs/nlohmann/json.hpp"

Logger::Logger(const std::string &logFileName, const std::string &jsonFileName, bool logToConsole)
    : logToConsole(logToConsole) {
    fileStream.open(logFileName, std::ios::out | std::ios::app);
    if (!fileStream.is_open()) {
        throw std::runtime_error("Kan logbestand niet openen: " + logFileName);
    }

    jsonFileStream.open(jsonFileName, std::ios::out | std::ios::app);
    if (!jsonFileStream.is_open()) {
        throw std::runtime_error("Kan JSON-bestand niet openen: " + jsonFileName);
    }

    phaseLogs = nlohmann::json::object();
}


Logger::~Logger() {
    if (fileStream.is_open()) {
        fileStream.close();
    }

    if (jsonFileStream.is_open()) {
        finalizeJson();
        jsonFileStream.close();
    }
}


void Logger::log(Level level, const std::string &message) {
    if (level < minLogLevel) return;


    std::string levelStr = getLevelString(level);
    std::string logMessage = "[" + currentPhase + "] [" + levelStr + "] " + message;
    currentPhase = getPhaseNumber(currentPhase);



    if (fileStream.is_open()) {
        fileStream << logMessage << std::endl;
    }


    nlohmann::json logEntry;
    logEntry["level"] = levelStr;
    logEntry["message"] = message;
    phaseLogs[currentPhase].push_back(logEntry);


    if (logToConsole) {
        std::cout << logMessage << std::endl;
    }
}

void Logger::finalizeJson() {

    if (jsonFileStream.is_open()) {
        jsonFileStream << phaseLogs.dump(4) << std::endl;
    }
}

std::string Logger::getPhaseNumber(const std::string& phaseName) {
    if(phaseName == "Initialization" || phaseName == "Finalization") {
        return phaseName;
    }
    std::string phaseNumber = phaseName;
    phaseNumber.erase(std::remove_if(phaseNumber.begin(), phaseNumber.end(), [](char c) { return !std::isdigit(c); }), phaseNumber.end());
    return phaseNumber;
}


void Logger::setLogLevel(Level level) {
    minLogLevel = level;
}

void Logger::setPhase(const std::string &phaseName) {
    currentPhase = phaseName;

    if (!logData["phases"].contains(currentPhase)) {
        logData["phases"][currentPhase] = nlohmann::json::array();
    }
}

std::string Logger::getLevelString(Level level) const {
    switch (level) {
        case INFO: return "INFO";
        case DEBUG: return "DEBUG";
        case WARN: return "WARN";
        case RUN: return "RUN";
        default: return "UNKNOWN";
    }
}
