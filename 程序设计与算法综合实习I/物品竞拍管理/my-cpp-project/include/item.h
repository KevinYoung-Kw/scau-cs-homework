#ifndef ITEM_H
#define ITEM_H

class Item {
public:
    Item();  // Default constructor
    Item(const std::string& name, double price);  // Parameterized constructor

    std::string getName() const;
    double getPrice() const;

    void setName(const std::string& name);
    void setPrice(double price);

private:
    std::string name;
    double price;
};

#endif // ITEM_H