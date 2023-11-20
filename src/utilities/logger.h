#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>

enum class MessageType {
    None,
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Fatal
};

/**
 * @brief Logs a message with the specified type, source, and message content.
 *
 * This function is used to log messages of different types, such as informational,
 * warning, or error messages, to provide visibility into the program's behavior.
 *
 * @param type    The type of the message (e.g., MessageType::Info, MessageType::Warning, MessageType::Error).
 * @param source  The source or context where the message originated (e.g., function name, module name).
 * @param message The actual message content to be logged.
 *
 * Usage Example:
 *
 *     // Logging an informational message
 *     Log(MessageType::Info, "MainFunction", "Program started successfully.");
 *
 *     // Logging a warning message
 *     Log(MessageType::Warning, "DataProcessor", "Input data format is not recognized.");
 *
 *     // Logging an error message
 *     Log(MessageType::Error, "FileIO", "Failed to open the input file.");
 *
 * Ensure that the necessary setup for logging (e.g., configuring log levels, output destinations)
 * is done before using this function to ensure proper logging behavior.
 */
void Log(MessageType type, const std::string& source, const std::string& message);

void InitLogger();
void CleanUpLogger();

#endif
