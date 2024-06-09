#ifndef USERQUEUE_H
#define USERQUEUE_H

#include <queue>
#include <initializer_list>
#include <string>
#include <cstring>
#include <fstream>
#include "User.h"
#include "tool.h"

class UserQueue {
private:
    std::deque<User> users;

public:
    UserQueue();
    UserQueue(std::initializer_list<User> users);
    UserQueue(const std::deque<User>& users);

    void clear();

    User findUser(const std::string& name);
    void switchUser();
    void addUser(const User& user);
    void addUser();
    void showUsers() const;
    void deleteUser(const std::string& name);
    UserQueue getUsers() const;

    std::size_t size() const;
    bool empty() const;
    User& front();
    User& back();
    std::deque<User>::iterator begin();
    std::deque<User>::iterator end();
    void push(const User& user);
    void pop();

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    
    static std::string getItemOnAuction(Bid &HighestBid, Item &item, UserQueue &users);
};

#endif  // USERQUEUE_H
