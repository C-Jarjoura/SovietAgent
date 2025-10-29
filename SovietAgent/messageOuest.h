#pragma once
#include <string>

class MessageOuest {
private:
    std::string messageMorse;
    std::string instructions;

public:
    MessageOuest();
    MessageOuest(const std::string& morse, const std::string& instr);

    std::string getMessageMorse() const;
    std::string getInstructions() const;

    void genererMessageAleatoire(double probabiliteMessage);
    void afficherDebug() const;
};
