#include "userQueue.h"
#include <iostream>

UserQueue::UserQueue() {
    users = std::deque<User>();
}

UserQueue::UserQueue(std::initializer_list<User> users) 
    : users(users) {}

UserQueue::UserQueue(const std::deque<User>& users) {
    this->users = users;
}

bool UserQueue::empty() const {
    return users.empty();
}

void UserQueue::clear() {
    users.clear();
}

size_t UserQueue::size() const {
    return users.size();
}

User& UserQueue::front() {
    return users.front();
}

User& UserQueue::back() {
    return users.back();
}

void UserQueue::push(const User& user) {
    users.push_back(user);
}

void UserQueue::pop() {
    users.pop_front();
}


User UserQueue::findUser(const std::string& name) {
    for (size_t i = 0; i < users.size(); ++i) {
        User user = users.front();
        users.pop_front();
        if (user.getName() == name){
            std::cout << "User found" << std::endl;
            users.push_back(user);
            return user;
        }
        users.push_back(user);
    }
    throw std::runtime_error("User not found");
}

void UserQueue::switchUser() {
    if (!users.empty()) {
        User user = users.front();
        users.pop_front();
        users.push_back(user);
    }
}

void UserQueue::addUser(const User& user) {
    users.push_back(user);
}

void UserQueue::addUser() {
    User user;
    user.InitUser();
    users.push_back(user);
}
void UserQueue::showUsers() const {
    UserQueue users = this->users;
    std::cout << "------------------------------UserQueue---------------------------------\n";
    for (size_t i = 0; i < users.size(); ++i) {
        User user = users.front();
        users.pop();
        std::cout << "User name:\t " << user.name << " Budget:\t" << user.budget << std::endl;
        users.push(user);
    }
    std::cout << "------------------------------------------------------------------------\n";
}

void UserQueue::deleteUser(const std::string& name) {
    size_t size = users.size();
    for (size_t i = 0; i < size; ++i) {
        User user = users.front();
        users.pop_front();
        if (user.name != name) {
            users.push_back(user);
        }
    }
}


UserQueue UserQueue::getUsers() const
{
    return UserQueue();
}
std::deque<User>::iterator UserQueue::begin() {
    return users.begin();
}
std::deque<User>::iterator UserQueue::end() {
    return users.end();
}

std::string UserQueue::getItemOnAuction(Bid& HighestBid, Item& item, UserQueue& users) {
    for (size_t i = 0; i < users.size(); ++i) {
        User user = users.front();
        users.pop();
        std::cout << user.name << std::endl;
        if (user.name == HighestBid.user) {
            std::cout << "User found" << std::endl;
            user.getItem(HighestBid, item);
            users.push(user);
            return "Item successfully purchased.";
        }
        users.push(user);
        
    }
    throw std::runtime_error("User not found");
}

void UserQueue::saveToFile(const std::string& filename) {
   std::string file = filename + ".user";
    std::ofstream outFile(file);
    if (!outFile) {
        std::cerr << "Failed to open file for writing." << std::endl;
        Tool::pause();
        return;
    }

    outFile << users.size() << "\n";
    for (const User& user : users) {
        outFile << user.name << "\n";
        outFile << user.budget << "\n";

    }

    outFile.close();
}

void UserQueue::loadFromFile(const std::string& filename) {
    std::string file = filename + ".user";
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return;
    }

    size_t size;
    inFile >> size;
    users.clear();
    for (size_t i = 0; i < size; ++i) {
        User user;
        inFile >> user.name;
        inFile >> user.budget;
        users.push_back(user);
    }

    inFile.close();
}