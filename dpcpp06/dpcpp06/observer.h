#pragma once
#include <iostream>
#include <vector>
#include <fstream>

class Observer {
public:
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

class Warning :public Observer
{
public:
    virtual void onWarning(const std::string& message) override
    {
        std::cout << message << std::endl;
    }
};

class Error :public Observer
{
public:
    virtual void onError(const std::string& message) override
    {
        std::ofstream out("Error.txt");
        if (out.is_open())
        {
            out << message << std::endl;
            out.close();
        }
    }
};
class FatalError :public Observer
{
public:
    virtual void onFatalError(const std::string& message) override
    {
        std::cout << message << std::endl;

        std::ofstream out("FatalError.txt");
        if (out.is_open())
        {
            out << message << std::endl;
            out.close();
        }
    }
};