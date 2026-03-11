#pragma once
#include <vector>
#include <algorithm>
#include "observer.h"

class Observable {
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

protected:
    void notify() {
        for (auto obs : observers)
            obs->update();
    }
};
