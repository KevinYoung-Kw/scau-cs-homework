#ifndef OPTION_H
#define OPTION_H

#include "Auction.h"
#include <string>
#include <vector>

class Option {
private:
    Auction* auction;
public:
    Option();
    ~Option();

    void createAndSaveAuction();
    void loadAuctionFromFile();
    void startAuction();
    std::string getName();
    std::string getDate();
    // void modifyAuction();
};

#endif // OPTION_H