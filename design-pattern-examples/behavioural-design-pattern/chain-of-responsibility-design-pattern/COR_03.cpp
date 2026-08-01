/* Design Logging Framework

Build a log level filter chain where each logger handles messages at or above its level. 
A DebugLogger handles all messages, InfoLogger handles INFO and above, WarnLogger handles WARN and above, and ErrorLogger handles only ERROR. 
Each logger prints the message at its level and passes it to the next logger.

Requirements:

LogLevel constants: DEBUG=1, INFO=2, WARN=3, ERROR=4
LogMessage class with level and message fields
Logger interface with setNext() and log() methods
BaseLogger abstract class with forwarding logic
DebugLogger handles level >= 1, prints [DEBUG] message
InfoLogger handles level >= 2, prints [INFO] message
WarnLogger handles level >= 3, prints [WARN] message
ErrorLogger handles level >= 4, prints [ERROR] message */

#include <iostream>
using namespace std;

enum LogLevel {
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4
};

class LogMessage {
    int level;
    string message;
    public:
        LogMessage(int level, string message) {
            this->level = level;
            this->message = message;
        }

        int getLevel() {
            return level;
        }

        string getMessage() {
            return message;
        }
};

class LoggerHandlerInterface {
    public:
        virtual void setNext(LoggerHandlerInterface* next) = 0;
        virtual void handleLogRequest(LogMessage message) = 0;
        virtual ~LoggerHandlerInterface() = default;
};

class BaseLoggerHandler : public LoggerHandlerInterface {
    protected:
        LoggerHandlerInterface* next;
    public:
        BaseLoggerHandler() {
            this->next = nullptr;
        }

        void setNext(LoggerHandlerInterface* next) override {
            this->next = next;
        }

        void forward(LogMessage message) {
            if (next != nullptr) {
                next->handleLogRequest(message);
            }
        }
};

class DebugLoggerHandler : public BaseLoggerHandler {
    public:
        void handleLogRequest(LogMessage log) override {
            if (log.getLevel() >= DEBUG) {
                cout << "[DEBUG] " << log.getMessage() << endl;
            }
            forward(log);
        }
};

class InfoLoggerHandler : public BaseLoggerHandler {
    public:
        void handleLogRequest(LogMessage message) override {
            if (message.getLevel() >= INFO) {
                cout << "[INFO] " << message.getMessage() << endl;
            }
            forward(message);
        }
};

class WarnLoggerHandler : public BaseLoggerHandler {
    public:
        void handleLogRequest(LogMessage message) override {
            if (message.getLevel() >= WARN) {
                cout << "[WARN] " << message.getMessage() << endl;
            }
            forward(message);
        }
};

class ErrorLoggerHandler : public BaseLoggerHandler {
    public:
        void handleLogRequest(LogMessage message) override {
            if (message.getLevel() >= ERROR) {
                cout << "[ERROR] " << message.getMessage() << endl;
            }
            forward(message);
        }
};

int main() {

    BaseLoggerHandler* warn = new WarnLoggerHandler();
    BaseLoggerHandler* info = new InfoLoggerHandler();
    BaseLoggerHandler* debug = new DebugLoggerHandler();
    BaseLoggerHandler* error = new ErrorLoggerHandler();

    //COR formation
    debug->setNext(info);
    info->setNext(warn);
    warn->setNext(error);

    debug->handleLogRequest(LogMessage(2, "User logged in"));
    debug->handleLogRequest(LogMessage(4, "Database connection lost"));

    delete error;
    delete warn;
    delete info;
    delete debug;

    return 0;
}