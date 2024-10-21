#include "Logger.h"

Logger::Logger(LogLevel level, bool logToSerial)
    : _level(level), _logToSerial(logToSerial) {
}

void Logger::log(LogLevel level, const String &message) {
    if (level >= _level) {  // Only log messages at or above the current log level
        String levelStr;
        
        switch (level) {
            case INFO: levelStr = "INFO"; break;
            case WARNING: levelStr = "WARNING"; break;
            case ERROR: levelStr = "ERROR"; break;
            case DEBUG: levelStr = "DEBUG"; break;
        }

        String logMessage = "[" + levelStr + "] " + message;

        if (_logToSerial) {
            Serial.println(logMessage);
        }

        // Add code here to log to other outputs (e.g., SD card)
    }
}

void Logger::info(const String &message) {
    log(INFO, message);
}

void Logger::warning(const String &message) {
    log(WARNING, message);
}

void Logger::error(const String &message) {
    log(ERROR, message);
}

void Logger::debug(const String &message) {
    log(DEBUG, message);
}

void Logger::setLogLevel(LogLevel level) {
    _level = level;
}
