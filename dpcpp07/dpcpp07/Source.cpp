#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>

enum class MessageType
{
    FatalError,
    Error,
    Warning,
    UnknownMessage
};

class LogMessage
{
    std::string _message;
    MessageType _type;
    bool handled = false;

public:
    LogMessage(const std::string& message, MessageType type) : _message(message), _type(type) {}
    MessageType type() const { return _type; }
    const std::string& message() const { return _message; }
    void setHandled() { handled = true; }
    bool isHandled() const { return handled; }
};

class LogHandler
{
protected:
    std::shared_ptr<LogHandler> _nextHandler;
    bool _hasNextHandler = false;

public:
    void setNextHandler(const std::shared_ptr<LogHandler>& nextHandler)
    {
        _nextHandler = nextHandler;
        _hasNextHandler = true;
    }
    virtual void handle(LogMessage& logMessage)
    {
        if (_nextHandler)
        {
            _nextHandler->handle(logMessage);
        }
        else
        {
            std::cerr << "No handler found for message: " << logMessage.message() << std::endl;
        }
    }
};

class WarningHandler : public LogHandler
{
public:
    void handle(LogMessage& logMessage) override
    {
        if (logMessage.type() == MessageType::Warning)
        {
            std::cout << "Warning Handler: " << logMessage.message() << std::endl;
            logMessage.setHandled();
        }

        if (_hasNextHandler)
        {
            _nextHandler->handle(logMessage);
        }
        else if (!logMessage.isHandled())
        {
            std::cerr << "No handler found for message: " << logMessage.message() << std::endl;
        }
    }
};

class ErrorHandler : public LogHandler
{
public:
    void handle(LogMessage& logMessage) override
    {
        if (logMessage.type() == MessageType::Error)
        {
            std::ofstream out("error_log.txt");
            if (out.is_open())
            {
                out << logMessage.message() << std::endl;
                logMessage.setHandled();
                out.close();
            }
        }

        if (_hasNextHandler)
        {
            _nextHandler->handle(logMessage);
        }
        else if (!logMessage.isHandled())
        {
            std::cerr << "No handler found for message: " << logMessage.message() << std::endl;
        }
    }
};

class FatalErrorHandler : public LogHandler
{
public:
    void handle(LogMessage& logMessage) override
    {
        if (logMessage.type() == MessageType::FatalError)
        {
            logMessage.setHandled();
            throw std::runtime_error("Fatal Error Handler: " + logMessage.message());
        }

        if (_hasNextHandler)
        {
            _nextHandler->handle(logMessage);
        }
        else if (!logMessage.isHandled())
        {
            std::cerr << "No handler found for message: " << logMessage.message() << std::endl;
        }
    }
};

class UnknownMessageHandler : public LogHandler
{
public:
    void handle(LogMessage& logMessage) override
    {
        if (logMessage.type() == MessageType::UnknownMessage)
        {
            logMessage.setHandled();
            throw std::runtime_error("Unknown Message Handler: " + logMessage.message());
        }

        if (_hasNextHandler)
        {
            _nextHandler->handle(logMessage);
        }
        else if (!logMessage.isHandled())
        {
            std::cerr << "No handler found for message: " << logMessage.message() << std::endl;
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setlocale(LC_ALL, "Russian");

    try
    {
        auto fatalErrorHandler = std::make_shared<FatalErrorHandler>();
        auto errorHandler = std::make_shared<ErrorHandler>();
        auto warningHandler = std::make_shared<WarningHandler>();
        auto unknownMessageHandler = std::make_shared<UnknownMessageHandler>();

        fatalErrorHandler->setNextHandler(errorHandler);
        errorHandler->setNextHandler(warningHandler);
        //warningHandler->setNextHandler(unknownMessageHandler);

        LogMessage msg1("Fatal error occurred", MessageType::FatalError);
        LogMessage msg2("An error occurred", MessageType::Error);
        LogMessage msg3("This is a warning", MessageType::Warning);
        LogMessage msg4("Unknown message type", MessageType::UnknownMessage);

        //fatalErrorHandler->handle(msg1);
        fatalErrorHandler->handle(msg2);
        fatalErrorHandler->handle(msg3);
        fatalErrorHandler->handle(msg4);
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

