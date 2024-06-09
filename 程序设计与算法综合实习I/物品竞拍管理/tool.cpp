#include "tool.h"
#include <iostream>
#include <limits>

void Tool::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void Tool::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Tool::pause() {
    std::cout << "Press enter to continue...";
    std::cin.get();
}