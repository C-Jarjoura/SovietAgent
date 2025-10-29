#pragma once
#include <string>

enum class MotiveType {
    Tourism,
    Family,
    Business,
    Diplomat
};

inline std::string motiveToString(MotiveType m) {
    switch (m) {
    case MotiveType::Tourism:   return "Tourism";
    case MotiveType::Family:    return "Family";
    case MotiveType::Business:  return "Business";
    case MotiveType::Diplomat:  return "Diplomat";
    default: return "Unknown";
    }
}
