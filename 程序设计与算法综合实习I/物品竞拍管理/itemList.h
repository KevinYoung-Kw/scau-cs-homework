#ifndef ITEM_LIST_H
#define ITEM_LIST_H

#include <vector>
#include <string>
#include <fstream>
#include "Item.h"

class ItemList {
public:
    ItemList();
    ItemList(std::initializer_list<Item> items);
    ItemList(const std::vector<Item>& items);
    ~ItemList();

    void clear();

    void addItem(Item item);
    void addItem(const std::string& name, const std::string& condition, const std::string& description, double estimatedValue, const std::vector<std::string>& types);
    void modifyItem(int id, const std::string& modification);
    void deleteItem(int id);
    void showItems();
    void displayItem(int id);
    void displayItem(const std::string& name);
    void displayItemsByType(const std::string& type);
    Item* findItem(int id);

    std::vector<Item>::iterator begin();
    std::vector<Item>::iterator end();

    std::size_t size() const;
    bool empty() const;

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

    std::vector<Item> items;
    void printItem(const Item& item);
};

#endif // ITEM_LIST_H