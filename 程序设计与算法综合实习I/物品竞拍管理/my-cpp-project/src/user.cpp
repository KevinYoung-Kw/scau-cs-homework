#include "../include/user.h"

// Implementation of the User class

User::User() {
    // Constructor implementation
}

User::~User() {
    // Destructor implementation
}

void User::setName(const std::string& name) {
    // Set the name of the user
    this->name = name;
}

std::string User::getName() const {
    // Get the name of the user
    return name;
}

// Add more member function implementations here if needed