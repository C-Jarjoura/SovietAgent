#include "MessageOuest.h"
#include <random>
#include <iostream>
#include <windows.h>
#include <map>

// --- Morse parameters ---
static const int SHORT_BEEP_MS = 20;
static const int LONG_BEEP_MS = 40;
static const int GAP_SYMBOL_MS = 60;
static const int GAP_LETTER_MS = 80;
static const int GAP_WORD_MS = 100;
static const int MORSE_FREQ_HZ = 120;

// Morse conversion table
static std::map<char, std::string> MORSE_TABLE = {
    { 'A', ".-" },   { 'B', "-..." }, { 'C', "-.-." }, { 'D', "-.." },
    { 'E', "." },    { 'F', "..-." }, { 'G', "--." },  { 'H', "...." },
    { 'I', ".." },   { 'J', ".---" }, { 'K', "-.-" },  { 'L', ".-.." },
    { 'M', "--" },   { 'N', "-." },   { 'O', "---" },  { 'P', ".--." },
    { 'Q', "--.-" }, { 'R', ".-." },  { 'S', "..." },  { 'T', "-" },
    { 'U', "..-" },  { 'V', "...-" }, { 'W', ".--" },  { 'X', "-..-" },
    { 'Y', "-.--" }, { 'Z', "--.." },
    { '0', "-----" }, { '1', ".----" }, { '2', "..---" }, { '3', "...--" },
    { '4', "....-" }, { '5', "....." }, { '6', "-...." }, { '7', "--..." },
    { '8', "---.." }, { '9', "----." },
    { ' ', "/" }
};

static std::string toUpperASCII(const std::string& s) {
    std::string r = s;
    for (size_t i = 0; i < r.size(); ++i)
        if (r[i] >= 'a' && r[i] <= 'z') r[i] -= 32;
    return r;
}

static std::string encodeToMorse(const std::string& text) {
    std::string up = toUpperASCII(text);
    std::string morse;
    for (size_t i = 0; i < up.size(); ++i) {
        char c = up[i];
        auto it = MORSE_TABLE.find(c);
        if (it != MORSE_TABLE.end()) {
            morse += it->second;
            if (i + 1 < up.size()) morse += " ";
        }
    }
    return morse;
}

// --- Class methods ---
MessageOuest::MessageOuest()
    : active(false), morseCode(""), plainText("") {
}

// Probability 1.0 = always active
void MessageOuest::generateForDay(double probability) {
    forcedAllow.clear();
    active = false;
    morseCode.clear();
    plainText.clear();

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::bernoulli_distribution appear(probability);
    active = appear(gen);

    if (!active)
        return;

    std::uniform_int_distribution<int> pickMotive(0, 3);
    MotiveType chosen = static_cast<MotiveType>(pickMotive(gen));
    forcedAllow.insert(chosen);

    std::string chosenStr = motiveToString(chosen);
    plainText = "ALLOW " + chosenStr + " TODAY EVEN IF FORBIDDEN BY USSR";
    morseCode = encodeToMorse(plainText);
}

bool MessageOuest::overrides(MotiveType m) const {
    return forcedAllow.find(m) != forcedAllow.end();
}

// --- Play only when message from WEST is active ---
void MessageOuest::playMorse() const {
    if (!active || morseCode.empty())
        return;

    std::cout << "\n[MORSE TRANSMISSION FROM THE WEST]\n";
    std::cout << "Signal: " << morseCode << "\n";
    std::cout << "(Decoding secret order...)\n\n";

    for (size_t i = 0; i < morseCode.size(); ++i) {
        char c = morseCode[i];
        if (c == '.') {
            Beep(MORSE_FREQ_HZ, SHORT_BEEP_MS);
            Sleep(GAP_SYMBOL_MS);
        }
        else if (c == '-') {
            Beep(MORSE_FREQ_HZ, LONG_BEEP_MS);
            Sleep(GAP_SYMBOL_MS);
        }
        else if (c == '/') {
            Sleep(GAP_WORD_MS);
        }
        else if (c == ' ') {
            Sleep(GAP_LETTER_MS);
        }
    }
}

// --- Display only the West order, not the official policy ---
void MessageOuest::showDebug() const {
    if (!active) {
        std::cout << "No Morse transmission today.\n";
        return;
    }

    std::cout << "SECRET WEST ORDER:\n";
    std::cout << "  " << plainText << "\n";

    for (auto it = forcedAllow.begin(); it != forcedAllow.end(); ++it) {
        MotiveType m = *it;
        std::cout << "  - ALWAYS ALLOW " << motiveToString(m)
            << " TODAY (even if forbidden by USSR)\n";
    }
}
