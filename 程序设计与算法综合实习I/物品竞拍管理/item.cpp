#include <iostream>
#include "item.h"

int Item::nextId = 1;

Item::Item() {
    Id = 0;
    name = "";
    condition = "";
    description = "";
    estimatedValue = 0.0;
}

Item::Item(const Item &item){
    Id = item.Id;
    name = item.name;
    condition = item.condition;
    description = item.description;
    estimatedValue = item.estimatedValue;
    types = item.types;
    bids = item.bids;
}

Item::Item(const std::string& name, const std::string& condition, const std::string& description, double estimatedValue, const std::vector<std::string>& types)
    : Id(nextId++), name(name), condition(condition), description(description), estimatedValue(estimatedValue), types(types) {}


void Item::initItem() {
    Id = nextId++;
    Tool::clearInput(); // clear the input buffer

    std::cout << "Enter the name: ";
    std::getline(std::cin, name);
    std::cout << "Enter the condition: ";
    std::getline(std::cin, condition);
    std::cout << "Enter the description: ";
    std::getline(std::cin, description);
    std::cout << "Enter the estimated value: ";
    std::cin >> estimatedValue;
    std::cout << "Enter the type: ";

    Tool::clearInput(); // clear the input buffer

    setType();
}

void Item::modifyItem(const std::string& modification) {
    std::string mod = modification;
    if (mod.find("num")) {
        int num;
        std::cout << "Enter the new number: ";
        std::cin >> num;
        Tool::clearInput(); // clear the input buffer
        setNumber(num);
    }
    // ... (other if branches remain the same)
    else if (mod.find("value")) {
        double e;
        std::cout << "Enter the new estimated value: ";
        std::cin >> e;
        Tool::clearInput(); // clear the input buffer
        setEstimatedValue(e);
    }
    else if (mod.find("type")) {
        setType();
    }
    else {
        std::cout << "Invalid modification." << std::endl;
    }
}

void Item::addBid(const std::string user, double price) {
    if (bids.empty() || price > bids.back().price) {
        Bid bid;
        bid.user = user;
        bid.bidNumber = bids.size() + 1;
        bid.price = price;
        bids.push_back(bid);
        std::cout << "Bid added successfully." << std::endl;
    }
    else {
        std::cout << "Bid failed. The price must be higher than the previous bid." << std::endl;
    }
}

void Item::showBid() {
    if (bids.empty()) {
        std::cout << "No bids for this item." << std::endl;
        return;
    }
    else {
        std::cout << "Bids for item " << name << ":" << std::endl;

        for (const auto& bid : bids) {
            std::cout << "Bid number: " << bid.bidNumber << std::endl;
            std::cout << "User: " << bid.user << std::endl;
            std::cout << "Price: " << bid.price << std::endl;
        }
    }

}

void Item::showItem() {
    std::cout << "Number: " << Id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Condition: " << condition << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Estimated value: " << estimatedValue << std::endl;
    std::cout << "Types: ";
    for (const auto& type : types) {
        std::cout << type << " ";
    }
    std::cout << std::endl;
}

void Item::setNumber(int num) {
    Id = num;
}

void Item::setName(std::string n) {
    name = n;
}

void Item::setCondition(std::string c) {
    condition = c;
}

void Item::setDescription(std::string d) {
    description = d;
}

void Item::setEstimatedValue(double e) {
    estimatedValue = e;
}

void Item::setType() {
    Tool::clearInput(); // clear the input buffer
    std::string t;
    std::cout << "Enter the new type: ";
    while (1) {

        std::getline(std::cin, t);
        if (t == "done") {
            break;
        }
        types.push_back(t);
        std::cout << "Enter another type or type 'done' to finish: ";
    }
}

void Item::deleteItem() {
    Id = 0;
    name = "";
    condition = "";
    description = "";
    estimatedValue = 0.0;
}

bool Item::operator==(const Item& other) const {
    return Id == other.Id && name == other.name;
}

bool Item::operator!=(const Item& other) const {
    return Id != other.Id && name != other.name;
}

