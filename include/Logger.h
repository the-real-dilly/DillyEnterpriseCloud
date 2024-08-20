#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <exception>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

class Logger {
public:
    static Logger& getInstance();

    void log(LogLevel level, const std::string& message);
    void logException(const std::exception& ex, const std::string& customMessage = "");
    void setLogFile(const std::string& filename);
    void setConsoleLogging(bool enabled);
    void setLogLevel(LogLevel level);

private:
    Logger();
    ~Logger();

    std::ofstream logFile;
    std::mutex logMutex;
    bool consoleLogging;
    LogLevel logLevel;

    std::string getLogLevelString(LogLevel level);
    void logToFile(const std::string& message);
    void logToConsole(const std::string& message);
};

#endif 
