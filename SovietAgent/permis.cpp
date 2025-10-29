#include "Permis.h"
#include <iostream>

Permis::Permis()
    : name(""), motive(MotiveType::Tourism),
    decision(false), westOverride(false), proWest(false) {
}

Permis::Permis(const std::string& n, MotiveType m)
    : name(n), motive(m),
    decision(false), westOverride(false), proWest(false) {
}

const std::string& Permis::getName() const { return name; }
MotiveType Permis::getMotive() const { return motive; }
bool Permis::getDecision() const { return decision; }
void Permis::setDecision(bool d) { decision = d; }

void Permis::showDebug() const {
    std::cout << "Permit for " << name
        << " | Motive: " << motiveToString(motive)
        << " | Decision: " << (decision ? "ALLOW" : "DENY")
        << (westOverride ? " | WEST OVERRIDE" : "")
        << std::endl;
}
