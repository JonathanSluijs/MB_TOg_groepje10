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

/**
 * @class Logger
 * @brief A utility class for logging messages with various severity levels.
 *
 * Logger provides functionality to log messages for applications, usually
 * to assist debugging or track runtime information. It supports different levels
 * such as debug, info, warning, error, and may include features like setting
 * log levels and formatting output.
 *
 * The class encapsulates methods to manage and write log messages to various outputs
 * such as the console, a file, or other logging mechanisms, depending on the implementation.
 *
 * Typical usage involves specifying the type of message, its severity, and optional
 * time-stamping or categorization.
 *
 * Features and responsibilities might include:
 * - Writing logs to a desired output.
 * - Filtering messages based on severity level.
 * - Configuring log formatting and storage options.
 */
class Logger {
 /**
  *
  */
public:
    enum Level {
        INFO,
        DEBUG,
        WARN,
        RUN
    };

 /**
  * @class Logger
  * @brief A utility class for logging messages with different severity levels.
  *
  * The Logger class provides methods to log informational, warning, and error messages.
  * It can be configured to write logs to various outputs such as console, files, or external systems.
  * The user can also set the logging level to filter out lower-priority messages.
  *
  * The main functionality includes:
  * - Logging messages with varying severity levels (Info, Warning, Error).
  * - Configuring the log output and log formatting.
  * - Supporting thread-safe logging for concurrent applications.
  *
  * Example use cases include debugging applications, monitoring runtime events,
  * and recording error details for future analysis.
  */
 explicit Logger(const std::string &logFileName, const std::string &jsonFileName, bool logToConsole = true);

 /**
  * @brief Represents a class for managing user accounts in a system.
  *
  * This class provides functionalities to handle user account creation,
  * deletion, updating, and retrieval of account details. It encapsulates
  * all the necessary methods to ensure proper account lifecycle management,
  * while maintaining data integrity and security.
  */
 ~Logger();

 /**
  * @brief Logs a message to the intended output stream or logging system.
  *
  * This function is designed to track the application's behavior or for debugging purposes by recording
  * messages. It can be customized to log into a file, console, or any other output channel.
  *
  * @param message The text string containing the log message.
  * @param level The severity level of the log message, such as DEBUG, INFO, WARN, ERROR.
  * @return void This function does not return a value.
  */
 void log(Level level, const std::string &message);

 /**
  * @brief Sets the logging level for the application.
  *
  * This function allows configuration of the logging level, which determines
  * the verbosity of logs output by the application. By adjusting the log level,
  * users can filter the type of messages they wish to see (e.g., errors, warnings,
  * debug information, etc.).
  *
  * @param level The desired logging level. Typical levels may include:
  *              - 0: No logging
  *              - 1: Error logging
  *              - 2: Warning logging
  *              - 3: Info logging
  *              - 4: Debug logging
  *
  * @throw std::invalid_argument if the specified log level is outside the acceptable range.
  */
 void setLogLevel(Level level);

 /**
  * @brief Sets the phase of the object to the specified value.
  *
  * This function allows modifying the phase state of the object.
  * It may trigger additional state changes or actions depending on the underlying implementation.
  *
  * @param phase An integer value representing the desired phase.
  */
 void setPhase(const std::string &phaseName);

 /**
  * Closes a JSON object or array that is currently open, finalizing its structure.
  *
  * This function is typically used when constructing a JSON object or array programmatically,
  * marking the end of the current structure. It ensures that the JSON syntax is completed
  * correctly.
  *
  * @note Ensure that all child elements, if any, have been properly added before calling
  * this function.
  */
 void closeJson();

 /**
  * @class fileStream
  * @brief A class to handle file read/write operations.
  *
  * The fileStream class provides functionality to open, read, write,
  * and manage files, allowing for efficient file manipulation.
  * It abstracts the complexities of file operations and offers
  * a simple interface for handling file streams in a robust way.
  *
  * Public methods in this class include open, close, read, write,
  * and utility functions for checking file status, among others.
  *
  * Proper error handling mechanisms are included to ensure the
  * safety and integrity of file operations.
  */
 std::ofstream fileStream;
 /**
  * @class jsonFileStream
  * @brief A class to handle file streams specifically for JSON data.
  *
  * This class provides functionalities to interact with JSON file streams, including reading
  * from or writing to JSON files while managing the underlying stream operations appropriately.
  *
  * It encapsulates file stream operations and ensures compatibility with JSON input/output processing.
  *
  * Typical tasks handled by this class include:
  * - Opening and closing JSON files.
  * - Reading JSON data from a file.
  * - Writing JSON data to a file.
  *
  * The class aims to simplify file handling for JSON data and reduce boilerplate code.
  */
 std::ofstream jsonFileStream;
 /**
  * Finalizes the construction of a JSON object.
  *
  * This method performs any necessary actions to complete the JSON object
  * or stringify it, depending on the operations defined in its implementation.
  * It ensures that the JSON is in its final valid state, ready for further usage,
  * storage, or transmission.
  *
  * @return A finalized JSON representation, typically in the form of a string
  *         or the completed JSON object itself.
  */
 void finalizeJson();


 /**
  * @brief A mutex object used to synchronize access to logging operations.
  *
  * The `logMutex` is utilized to ensure thread-safe logging by preventing
  * concurrent threads from writing to the log simultaneously. It helps
  * maintain the consistency and integrity of log outputs in a multi-threaded
  * environment.
  */
private:
    std::mutex logMutex;
 /**
  * Defines the minimum logging level for the application.
  *
  * This variable is used to determine the lowest severity of log messages
  * that should be recorded or displayed. Log messages with a severity level
  * below this value will be ignored.
  *
  * Common usage includes setting this variable to control the verbosity
  * of log output, facilitating debugging and monitoring processes.
  *
  * Possible values typically correspond to predefined severity levels,
  * such as DEBUG, INFO, WARNING, ERROR, or CRITICAL, depending on the
  * logging framework or implementation in use.
  */
 Level minLogLevel = INFO;
 /**
  * Logs a specified message to the console.
  *
  * This function outputs a given message to the console, typically for debugging purposes
  * or for providing runtime information. It can be used to track application flow,
  * display values, or indicate errors.
  *
  * @param message The string to be logged in the console. This should be a human-readable
  * textual description or a runtime variable converted to a string.
  */
 bool logToConsole;
 /**
  * @brief Represents the current phase or stage in a process or workflow.
  *
  * This variable is used to track the specific state or progress in a procedural
  * sequence, aiding in control flow and decision-making within the application.
  */
 std::string currentPhase = "GENERAL";
 /**
  * @brief Stores the log data for the application or system.
  *
  * This variable is used to hold information related to logging,
  * such as system events, errors, or debug messages. The structure
  * and content of the log data will vary depending on the use case
  * and logging implementation.
  *
  * It is essential for monitoring system behavior, diagnosing issues,
  * and maintaining application performance by providing detailed
  * information during runtime.
  */
 nlohmann::json logData;
 /**
  * @brief Stores logs or records related to different phases of a process or operation.
  *
  * This variable is used to maintain a collection of log entries or details
  * corresponding to various phases in a workflow, process, or system
  * operations. Each entry in this variable may represent specific information
  * about a phase, such as timestamps, status updates, or messages.
  *
  * The data structure type and details depend on the implementation, and it
  * is used for tracking, debugging, or auditing purposes across multiple
  * phases.
  */
 nlohmann::json phaseLogs;

 /**
  * Converts a given level integer to its corresponding string representation.
  *
  * @param level An integer representing the level to be converted.
  * @return A string corresponding to the provided level. If the level is not recognized,
  *         a default or error string may be returned.
  */
 std::string getLevelString(Level level) const;

 /**
  * Retrieves the phase number of the current process or state.
  *
  * @return An integer representing the phase number.
  */
 std::string getPhaseNumber(const std::string &phaseName);

 /**
  * Writes a series of phase logs to a specified file.
  *
  * This method takes a collection of phase logs and writes their content into a
  * designated output file. Each log entry is processed and formatted before being
  * written to ensure readability and structure.
  *
  * @param logs A vector containing the phase logs to be written.
  * @param filePath The path of the output file where the logs will be saved.
  * @param append A boolean indicating whether to append to the file if it exists (true)
  *               or overwrite the file (false).
  * @param includeTimestamp A boolean indicating whether to include timestamps for each log entry.
  */
 void writePhaseLogsToFile(const std::string &filename);



};

#endif //LOGGER_H

