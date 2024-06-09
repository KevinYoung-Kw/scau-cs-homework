#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>
#include "tool.h"

struct Bid {
    std::string user;
    int bidNumber;
    double price;
};

class Item {
public:
    int Id;
    std::string name;
    std::string condition;
    std::string description;
    double estimatedValue;
    std::vector<std::string> types;
    std::vector<Bid> bids;

    Item();
    Item(const Item &item);
    Item(const std::string& name, const std::string& condition, const std::string& description, double estimatedValue, const std::vector<std::string>& types);


    void initItem();
    virtual void modifyItem(const std::string& modification);
    void addBid(const std::string user, double price);
    void showBid();
    void showItem();
    void deleteItem();
    bool operator==(const Item& other) const;
    bool operator!=(const Item& other) const;
    
    static int nextId;

    void setNumber(int num);
    void setName(std::string n);
    void setCondition(std::string c);
    void setDescription(std::string d);
    void setEstimatedValue(double e);
    void setType();

    
    
};

#endif // ITEM_H