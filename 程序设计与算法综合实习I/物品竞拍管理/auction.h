#ifndef AUCTION_H
#define AUCTION_H
#define NOMINMAX

const size_t MAX_TYPE_SIZE = 100;  // 你可以根据你的需求调整这个值
const size_t MAX_BID_SIZE = 100;   

#include "userQueue.h"
#include "itemList.h"
#include "tool.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <fstream>
#include <windows.h>

class Auction {
public:
    Auction();

    Auction(const std::string& name, const std::string& date);
    
    void InitItem();
    void InitItem(ItemList& items);
    void InitUser();
    void InitUser(UserQueue& users);
    void InitAuction();
    void InitAuction(const std::string& name, const std::string& date);
    
    bool checkAuction();
    void showAuction();
    void start();
    int getItemsCount();
    int getBiddedCount();
    double getTotalAmount();
    void settleAuction(Item& item);
    void showUserOwnItems();
    void showUserOwnItems(Auction auction);

    void auctionSelect();
    void saveAuction();
    void loadAuction(const std::string& filename);

    int menu(User& user, Item& item);
    std::string getName() const;
    std::string getDate() const;

private:
    UserQueue users;
    ItemList items;
    std::string auctionName;
    std::string auctionDate;
    double totalAmount;
    int bidCount;

};

#endif // AUCTION_H