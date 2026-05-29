#pragma once

#include <string>

// Kody kolorów ANSI do terminala
// Używamy inline żeby uniknąć błędu "multiple definition" przy dołączaniu do wielu plików .cpp

inline const std::string RESET = "\033[0m";
inline const std::string BOLD = "\033[1m";
inline const std::string RED = "\033[31m";
inline const std::string BLUE = "\033[34m";
inline const std::string YELLOW = "\033[33m";
inline const std::string GREEN = "\033[32m";
inline const std::string CYAN = "\033[36m";

