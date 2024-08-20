#include "../include/Logger.h"
#include <ctime>

Logger::Logger() : consoleLogging(true), logLevel(LogLevel::INFO) {}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);

    if (level >= logLevel) {
        std::string logMessage = "[" + getLogLevelString(level) + "] " + message;

        if (consoleLogging) {
            logToConsole(logMessage);
        }

        if (logFile.is_open()) {
            logToFile(logMessage);
        }
    }
}

void Logger::logException(const std::exception& ex, const std::string& customMessage) {
    std::lock_guard<std::mutex> lock(logMutex);

    std::string logMessage = "[EXCEPTION] " + std::string(ex.what());

    if (!customMessage.empty()) {
        logMessage += " - " + customMessage;
    }

    if (consoleLogging) {
        logToConsole(logMessage);
    }

    if (logFile.is_open()) {
        logToFile(logMessage);
    }
}

void Logger::setLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(logMutex);

    if (logFile.is_open()) {
        logFile.close();
    }

    logFile.open(filename, std::ios::app);

    if (!logFile.is_open()) {
        throw std::runtime_error("Unable to open log file: " + filename);
    }
}

void Logger::setConsoleLogging(bool enabled) {
    std::lock_guard<std::mutex> lock(logMutex);
    consoleLogging = enabled;
}

void Logger::setLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);
    logLevel = level;
}

std::string Logger::getLogLevelString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO:    return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR:   return "ERROR";
        case LogLevel::DEBUG:   return "DEBUG";
        default:                return "UNKNOWN";
    }
}

void Logger::logToFile(const std::string& message) {
    std::time_t now = std::time(nullptr);
    logFile << std::asctime(std::localtime(&now)) << message << std::endl;
}

void Logger::logToConsole(const std::string& message) {
    std::cout << message << std::endl;
}
