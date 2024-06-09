#ifndef USER_H
#define USER_H

#include <string>
#include "itemList.h"
#include "tool.h"
#include "item.h"

class User {
public:
    std::string name;
    double budget;
    ItemList userOwnItems = ItemList();
    ItemList userBidItems = ItemList();

    User();
    User(const std::string& name, double budget);
    
    void InitUser();
    std::string getName();
    void getBudget();
    void displayItem(int id);
    void displayItem(const std::string& name);
    void displayItemsByType(const std::string& type);
    void deleteItem(int id);
    void bidItem(int id, double price, ItemList &items);
    void bitItem(Item &item, double price);
    void getItem(int id, ItemList &items);
    void getItem(Bid HighestBid, Item& item);
    bool operator==(const User& other) const;
    User& operator=(const User& other);
    User* operator&();
};

#endif  // USER_H