#include "itemList.h"
#include <iostream>
#include <initializer_list>

ItemList::ItemList() {
    items = std::vector<Item>();
}

ItemList::ItemList(std::initializer_list<Item> items)
    : items(items) {}

ItemList::ItemList(const std::vector<Item>& items) {
    this->items = items;
}

ItemList::~ItemList() {
    items.clear();
}

void ItemList::clear() {
    items.clear();
}


void ItemList::addItem(Item item) {
    items.push_back(item);
}


void ItemList::addItem(const std::string& name, const std::string& condition, const std::string& description, double estimatedValue, const std::vector<std::string>& types) {
    items.push_back(Item(name, condition, description, estimatedValue, types));
}

void ItemList::modifyItem(int id, const std::string& modification) {
    for (auto& item : items) {
        if (item.Id == id) {
            item.modifyItem(modification);
            return;
        }
    }
    std::cout << "Item not found." << std::endl;
}

void ItemList::deleteItem(int id) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->Id == id) {
            items.erase(it);
            return;
        }
    }
    std::cout << "Item not found." << std::endl;
}

void ItemList::showItems() {
    for (const auto& item : items) {
        printItem(item);
    }
}

void ItemList::displayItem(int id) {
    for (const auto& item : items) {
        if (item.Id == id) {
            printItem(item);
            return;
        }
    }
    std::cout << "Item not found." << std::endl;
}

void ItemList::displayItem(const std::string& name) {
    for (const auto& item : items) {
        if (item.name == name) {
            printItem(item);
            return;
        }
    }
    std::cout << "Item not found." << std::endl;
}

void ItemList::displayItemsByType(const std::string& type) {
    for (const auto& item : items) {
        for (const auto& itemType : item.types) {
            if (itemType == type) {
                printItem(item);
                break;
            }
        }
    }
}

Item* ItemList::findItem(int id) {
    for (auto& item : items) {
        if (item.Id == id) {
            return &item;
        }
    }
    return nullptr;
}

void ItemList::printItem(const Item& item) {
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "Id: " << item.Id << std::endl;
    std::cout << "Name: " << item.name << std::endl;
    std::cout << "Condition: " << item.condition << std::endl;
    std::cout << "Description: " << item.description << std::endl;
    std::cout << "Estimated Value: " << item.estimatedValue << std::endl;
    std::cout << "Types: ";
    for (const auto& type : item.types) {
        std::cout << type << " ";
    }
    std::cout << "\n------------------------------------------------------------------------\n";
}

std::vector<Item>::iterator ItemList::begin() {
    return items.begin();
}

std::vector<Item>::iterator ItemList::end() {
    return items.end();
}
std::size_t ItemList::size() const{
    return items.size();
}

bool ItemList::empty() const {
    return items.empty();
}

void ItemList::saveToFile(const std::string& filename) {
    std::string file = filename + ".item";
    std::ofstream outFile(file);
    if (!outFile) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }

    outFile << items.size() << "\n";
    for (const Item& item : items) {
        outFile << item.Id << "\n";
        outFile << item.name << "\n";
        outFile << item.condition << "\n";
        outFile << item.description << "\n";
        outFile << item.estimatedValue << "\n";
        outFile << item.types.size() << "\n";
        for (const auto& type : item.types) {
            outFile << type << "\n";
        }
    }

    outFile.close();
}

void ItemList::loadFromFile(const std::string& filename) {
    std::string file = filename + ".item";
    std::ifstream inFile(file);
    if (!inFile) {
        std::cerr << "Failed to open file for reading." << std::endl;
        Tool::pause();
        return;
    }

    size_t size;
    inFile >> size;
    items.clear();
    for (size_t i = 0; i < size; ++i) {
        Item item;
        inFile >> item.Id;
        inFile >> item.name;
        inFile >> item.condition;
        inFile >> item.description;
        inFile >> item.estimatedValue;
        size_t typesSize;
        inFile >> typesSize;
        item.types.clear();
        for (size_t j = 0; j < typesSize; ++j) {
            std::string type;
            inFile >> type;
            item.types.push_back(type);
        }
        items.push_back(item);
    }

    inFile.close();
}