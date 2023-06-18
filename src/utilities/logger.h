#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

enum class MessageType {
    NONE,
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

void InitLogger();
void CleanUpLogger();

void Log(MessageType type, const std::string& source, const std::string& message);

#endif