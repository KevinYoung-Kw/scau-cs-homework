#include "../include/item.h"

// Item class implementation

Item::Item() {
    // Constructor implementation
}

Item::~Item() {
    // Destructor implementation
}

void Item::setName(const std::string& name) {
    // Set the name of the item
    this->name = name;
}

std::string Item::getName() const {
    // Get the name of the item
    return name;
}

void Item::setPrice(double price) {
    // Set the price of the item
    this->price = price;
}

double Item::getPrice() const {
    // Get the price of the item
    return price;
}

// Other member function implementations