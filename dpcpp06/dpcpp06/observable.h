#pragma once
#include "observer.h"

class Observable
{
    std::vector<Observer*> _obs;
public:
    void AddObserver(Observer* obs)
    {
        _obs.push_back(obs);
    }
    void RemoveObserver(Observer* obs)
    {
        _obs.erase(std::remove(_obs.begin(), _obs.end(), obs));
    }
    void CallWarning(const std::string& message) const
    {
        for (auto& observer : _obs)
        {
            if (observer)
            {
                observer->onWarning(message);
            }
        }
    }
    void CallError(const std::string& message) const
    {
        for (auto& observer : _obs)
        {
            if (observer)
            {
                observer->onError(message);
            }
        }
    }
    void CallFatalError(const std::string& message) const
    {
        for (auto& observer : _obs)
        {
            if (observer)
            {
                observer->onFatalError(message);
            }
        }
    }
};