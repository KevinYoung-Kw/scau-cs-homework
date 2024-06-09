#include <iostream>
#include "user.h"


User::User() {
    name = "";
    budget = 0.0;  // 初始化budget
    userOwnItems = ItemList();
    userBidItems = ItemList();
}

User::User(const std::string& name, double budget)
    : name(name), budget(budget), userOwnItems(ItemList()), userBidItems(ItemList()) {}

void User::InitUser() {
    std::string name;
    double budget;
    Tool::clearInput();

    std::cout << "Enter the name: ";
    std::getline(std::cin, name);

    std::cout << "Enter the budget: ";
    std::cin >> budget;

    this->name = name;
    this->budget = budget;
}

std::string User::getName() {
    return name;
}

void User::displayItem(int id) {
    userBidItems.displayItem(id);
}

void User::displayItem(const std::string& name) {
    userBidItems.displayItem(name);
}

void User::displayItemsByType(const std::string& type) {
    userBidItems.displayItemsByType(type);
}

void User::deleteItem(int id) {
    userBidItems.deleteItem(id);
}

bool User::operator==(const User& other) const {
    return this->name == other.name && this->budget == other.budget;
}

void User::bidItem(int id, double price, ItemList &items) {
    if (price > budget) {  // 如果竞标价格大于budget，直接返回
        std::cout << "Insufficient budget for this bid." << std::endl;
        return;
    }

    Item* bidItem = items.findItem(id);
    if ((*bidItem) != Item())  // 如果找到了该item
    {
        (*bidItem).addBid(this->name, price); // 暂时不扣除金额，竞标成功后，才从budget中扣除竞标价格
        userBidItems.addItem((*bidItem));
        std::cout << "Bid successful." << std::endl;
    }
    else
    {
        std::cout << "Item not found." << std::endl;
    }
}

void User::bitItem(Item &item, double price) {
    if (price > budget) {
        std::cout << "Insufficient budget for this bid." << std::endl;
        return;
    }

    item.addBid(this->name, price);
    userBidItems.addItem(item);
    std::cout << "Bid successful." << std::endl;
}

void User::getItem(int id, ItemList &items) {
    Item* item = items.findItem(id);
    if ((*item) != Item()) {
        userOwnItems.addItem((*item));
        budget -= (*item).bids[0].price;  // 从budget中扣除竞标价格
        std::cout << "Item successfully purchased." << std::endl;
    }
    else {
        std::cout << "Item not found." << std::endl;
    }
}

void User::getItem(Bid HighestBid, Item& item) {
    userOwnItems.addItem(item);
    budget -= HighestBid.price;
    std::cout << "Item successfully purchased." << std::endl;
}
void User::getBudget() {
    std::cout << "Your budget is: " << budget << std::endl;
}

User& User::operator=(const User& other) {
    if (this != &other) {
        this->name = other.name;
        this->budget = other.budget;
        this->userOwnItems = other.userOwnItems;
        this->userBidItems = other.userBidItems;
    }
    return *this;
}

User* User::operator&() {
    return this;
}