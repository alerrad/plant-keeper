#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

enum LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

class Logger {
private:
    LogLevel _level;
    bool _logToSerial;  // Flag to enable or disable serial logging
    // Optionally, you can add other logging options like SD card
public:
    Logger(LogLevel level, bool logToSerial = true);  // Constructor
    
    void log(LogLevel level, const String &message);
    void info(const String &message);
    void warning(const String &message);
    void error(const String &message);
    void debug(const String &message);
    void setLogLevel(LogLevel level);
};

#endif
