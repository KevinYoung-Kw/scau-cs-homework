#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "item.h"

class ItemList {
public:
    ItemList();
    ~ItemList();

    void addItem(const Item& item);
    void removeItem(const Item& item);
    void displayItems() const;

private:
    // Private member variables
    // ...

    // Private member functions
    // ...
};

#endif // ITEMLIST_H