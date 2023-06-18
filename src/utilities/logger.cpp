#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "logger.h"

std::ofstream fileStream;
sf::Clock appClock;

void Log(MessageType type, const std::string& source, const std::string& message) {

    // Get TimeStamp
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto now_ms_value = now_ms.time_since_epoch().count();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time_t);
    int milliseconds = static_cast<int>(now_ms_value % 1000);
    std::ostringstream oss;
    oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setw(3) << std::setfill('0') << milliseconds;
    std::string timestamp = oss.str();

    // Get Message Type
    std::string messageType;
    switch (type) {
        case MessageType::NONE:
            messageType = "";
            break;
        case MessageType::TRACE:
            messageType = "[TRACE] ";
            break;
        case MessageType::DEBUG:
            messageType = "[DEBUG] ";
            break;
        case MessageType::INFO:
            messageType = "[INFO] ";
            break;
        case MessageType::WARN:
            messageType = "[WARN] ";
            break;
        case MessageType::ERROR:
            messageType = "[ERROR] ";
            break;
        case MessageType::FATAL:
            messageType = "[FATAL] ";
            break;}
    
    // Get Source
    std::string formattedSource = source;
    if (!formattedSource.empty()) {
        formattedSource += ": ";
    }

    // Log Message
    fileStream << "[" << timestamp << "] " << formattedSource << messageType << message << std::endl;
    std::cout << "[" << timestamp << "] " << formattedSource << messageType << message << std::endl;
}

void InitLogger() {
    // Get Filename
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time_t);
    std::ostringstream oss;
    oss << std::put_time(now_tm, "%Y%m%d_%H%M%S");
    std::string filename = oss.str();

    fileStream.open(("logs/" + filename + ".log"), std::ios::app);

    // Get TimeStamp
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto now_ms_value = now_ms.time_since_epoch().count();
    int milliseconds = static_cast<int>(now_ms_value % 1000);
    std::ostringstream ossms;
    ossms << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");
    ossms << '.' << std::setw(3) << std::setfill('0') << milliseconds;
    std::string timestamp = "Started new log on " + ossms.str();

    // Start Log
    Log(MessageType::NONE, "", timestamp);
    Log(MessageType::NONE, "", "====================================================================================================");
}

void CleanUpLogger() {
    sf::Time elapsedTime = appClock.getElapsedTime();
    Log(MessageType::NONE, "", ("Stopping! Time elapsed: " + std::to_string((int)(elapsedTime.asSeconds() * 1000)) + " ms."));
    if (fileStream.is_open())
        fileStream.close();
}