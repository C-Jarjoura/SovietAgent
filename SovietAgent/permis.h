#pragma once
#include <iostream>
#include <string>
#include "Motive.h"

class Permis {
private:
    std::string name;
    MotiveType motive;
    bool decision;
    bool westOverride;
    bool proWest;

public:
    Permis();
    Permis(const std::string& n, MotiveType m);

    const std::string& getName() const;
    MotiveType getMotive() const;
    bool getDecision() const;
    void setDecision(bool d);

    void setWestOverride(bool v) { westOverride = v; }
    bool hasWestOverride() const { return westOverride; }

    void setProWest(bool v) { proWest = v; }
    bool isProWest() const { return proWest; }

    void showDebug() const;
};
