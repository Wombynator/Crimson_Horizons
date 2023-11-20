#include "logger.h"


std::ofstream fileStream;
std::ofstream outputFile("output.txt");
std::streambuf* originalOut;
auto start = std::chrono::high_resolution_clock::now();


std::string getCurrentDateTimeString(const std::string& dateSeparator, const std::string& dateTimeSeparator, const std::string& timeSeparator, const std::string& msSeparator, bool includeMilliseconds) {
    // Get the current system time
    auto now = std::chrono::system_clock::now();

    // Convert the system time to a timepoint
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Initialize a tm struct to store the time components
    std::tm timeInfo;

    // Use localtime_s to fill the tm struct (thread-safe version)
    if (localtime_s(&timeInfo, &currentTime) != 0) {
        // Handle error if localtime_s fails
        return "Error: Unable to get local time.";
    }

    // Format the components into a string
    std::ostringstream oss;
    oss << std::setfill('0');
    oss << std::setw(4) << timeInfo.tm_year + 1900 << dateSeparator;
    oss << std::setw(2) << timeInfo.tm_mon + 1 << dateSeparator;
    oss << std::setw(2) << timeInfo.tm_mday << dateTimeSeparator;
    oss << std::setw(2) << timeInfo.tm_hour << timeSeparator;
    oss << std::setw(2) << timeInfo.tm_min << timeSeparator;
    oss << std::setw(2) << timeInfo.tm_sec;

    if (includeMilliseconds) {
        oss << msSeparator;
        oss << std::setw(3) << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
    }

    return oss.str();
}


void Log(MessageType type, const std::string& source, const std::string& message) {

    // Get TimeStamp
    std::string timestamp = getCurrentDateTimeString("-", " ", ":", ".", true);

    // Get Message Type
    std::string messageType;
    std::string messageColor;
    switch (type) {
    case MessageType::None:
        messageType = "";
        break;
    case MessageType::Trace:
        messageType = "[TRACE] ";
        messageColor = "\033[38;5;175m"; //Purple
        break;
    case MessageType::Debug:
        messageType = "[DEBUG] ";
        messageColor = "\033[38;5;111m"; //Blue
        break;
    case MessageType::Info:
        messageType = "[INFO] ";
        messageColor = "\033[38;5;112m"; //Green
        break;
    case MessageType::Warning:
        messageType = "[WARN] ";
        messageColor = "\033[38;2;255;170;00m"; //Orange
        break;
    case MessageType::Error:
        messageType = "[ERROR] ";
        messageColor = "\033[38;2;255;85;85m"; //Red
        break;
    case MessageType::Fatal:
        messageType = "[FATAL] ";
        messageColor = "\033[48;2;170;0;0m"; //Dark Red Background
        break;
    }

    // Get Source
    std::string formattedSource = source;
    if (!formattedSource.empty()) {
        formattedSource += ": ";
    }

    // Log Message
    std::cout.rdbuf(originalOut);
    fileStream << "[" << timestamp << "] " << formattedSource << messageType << message << std::endl;
    std::cout << "\033[38;5;112m" << "[" << timestamp << "] " << "\033[38;5;111m" << formattedSource << "\033[0m" << messageType  << messageColor << message << "\033[0m" << std::endl;
    originalOut = std::cout.rdbuf(outputFile.rdbuf());
}

void InitLogger() {
    // Redirect stdout to a file
    originalOut = std::cout.rdbuf(outputFile.rdbuf());

    // Create log file: YYYY-MM-DD_HH-MM-SS.log
    fileStream.open(("logs/" + getCurrentDateTimeString("-", "_", "-", " ", false) + ".log"), std::ios::app);

    // Start Log
    Log(MessageType::None, "", ("Started new log on " + getCurrentDateTimeString("-", " ", ":", ".", true)));
    Log(MessageType::None, "", "==============================================================================================");
}

// Log Message: [YYYY-MM-DD HH:MM:SS.MS] Stopping! Time elapsed: XXXX ms.
// Closes File
void CleanUpLogger() {
    int duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    int hours = duration / 1000 / 60 / 60;
    int minutes = (duration - hours * 1000 * 60 * 60) / 1000 / 60;
    int seconds = (duration - hours * 1000 * 60 * 60 - minutes * 1000 * 60) / 1000;
    int rest = duration % 1000;
    Log(MessageType::None, "", ("Stopping! Time elapsed: " + std::to_string(duration) + " ms. (" + std::to_string(hours) + "h " + std::to_string(minutes) + "m " + std::to_string(seconds) + "s " + std::to_string(rest) + "ms)"));
    if (fileStream.is_open())
        fileStream.close();
}