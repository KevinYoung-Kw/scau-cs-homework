#include "auction.h"
#include <iostream>
#include <algorithm>

Auction::Auction() : auctionName(""), auctionDate(""), totalAmount(0.0) {}

Auction::Auction(const std::string& name, const std::string& date)
    : auctionName(name), auctionDate(date), totalAmount(0.0) {}

void Auction::InitItem() {
    int num;
    std::cout << "Please enter the number of items: ";
    std::cin >> num;
    if (num <= 0) {
        std::cout << "Invalid number of items" << std::endl;
        return;
    }
    Item item;
    while (num-- > 0)
    {
        Tool::clearScreen();
        Item item;
        item.initItem();
        items.addItem(item);
        Tool::pause();
    }
    std::cout << "Item initialization completed" << std::endl;
    Tool::pause();
    Tool::clearScreen();
}

void Auction::InitItem(ItemList& items) {
    Auction::items = items;
    items.showItems();
    Tool::pause();
    Tool::clearScreen();
}

void Auction::InitUser() {
    int num;
    Tool::clearInput();
    std::cout << "Please enter the number of users: ";
    std::cin >> num;
    Tool::clearInput();

    if (num <= 0) {
        std::cout << "Invalid number of users" << std::endl;
        return;
    }

    while (num-- > 0)
    {
        User user;
        user.InitUser();
        users.addUser(user);
    }
    std::cout << "User initialization completed" << std::endl;
    Tool::pause();
    Tool::clearScreen();
}

void Auction::InitUser(UserQueue& users) {
    Auction::users = users;
    users.showUsers();
    Tool::pause();
    Tool::clearScreen();
}

void Auction::InitAuction() {
    std::string name;
    std::string date;
    std::cout << "Please enter the name of the auction: ";
    std::getline(std::cin, name);
    auctionName = name;
    std::cout << "Please enter the date of the auction: ";
    std::getline(std::cin, date);
    auctionDate = date;

    InitItem();
    InitUser();

    std::cout << "Auction initialization completed" << std::endl;
    Tool::pause();
    Tool::clearScreen();
}

void Auction::InitAuction(const std::string& name, const std::string& date) {
    auctionName = name;
    auctionDate = date;
}

bool Auction::checkAuction() {
    return !items.empty() && !users.empty();
}

void Auction::showAuction() {
    std::cout << "------------------------------------------------\n";
    std::cout << " Auction name: \t\t" << auctionName << " \n";
    std::cout << " Auction date: \t\t" << auctionDate << " \n";
    std::cout << "------------------------------------------------\n";
    std::cout << " The list of items is as follows: \n";
    items.showItems();
    std::cout << "------------------------------------------------\n";
    std::cout << " The list of users is as follows: \n";
    users.showUsers();
    std::cout << "------------------------------------------------\n";
    Tool::pause();
    Tool::clearScreen();
}
void Auction::start() {
    if (items.empty() || users.empty()) {
        std::cout << "The list of items or users is empty, and the auction cannot start." << std::endl;
        return;
    }

    for (auto& item : items) {
        std::cout << "Start bidding for the item: " << item.name << std::endl;

        int bidCount = 0;
        bool isBidding = true;

        while(isBidding) {
            for (auto& user : users) {
                if (user.budget <= 0) {
                    std::cout << "The user " << user.name << " has no budget and cannot participate in the auction." << std::endl;
                    continue;
                }
                std::cout << "User " << user.name << " is bidding for the item " << item.name << std::endl;
                int choice = menu(user, item);
                if (choice == 3) {
                    bidCount = 0;
                }
                
                if (choice == 8) {
                    bidCount++;
                }

                if (bidCount == users.size()) {
                    std::cout << "The auction for the item " << item.name << " has ended" << std::endl;
                    settleAuction(item);
                    bidCount = 0;
                    isBidding = false;
                    break;
                }

            }

        }

    }
}

void Auction::auctionSelect() {
    std::vector<std::string> files;
    std::string path = ".\\*"; // Change this to the directory where your auction files are stored

    // Get all files in the directory
    WIN32_FIND_DATA data;
    HANDLE hFind;
    if ((hFind = FindFirstFile(path.c_str(), &data)) != INVALID_HANDLE_VALUE) {
        do {
            if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                files.push_back(data.cFileName);
            }
        } while (FindNextFile(hFind, &data) != 0);
        FindClose(hFind);
    }

    // Let the user select a file
    int choice;
    do {
        std::cout << "Select an auction file:\n";
        for (size_t i = 0; i < files.size(); ++i) {
            std::cout << i + 1 << ". " << files[i] << "\n";
        }
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        --choice;
    } while (choice < 0 || choice >= files.size());

    // Load the selected file
    loadAuction(files[choice]);
}

int Auction::menu(User& user, Item& currentItem) {
    int choice;
    do {
        Tool::clearScreen();
        std::cout << "------------------------------------------------------------------------\n";
        std::cout << "| User: \t\t" << user.name << " \n";
        std::cout << "| Item: \t\t" << currentItem.name << " \n";
        std::cout << "------------------------------------------------------------------------\n";
        std::cout << "| 1. View the bids of others for the current auction item \n"
            << "| 2. View detailed information of the current auction item \n"
            << "| 3. Bid |\n"
            << "| 4. View the goods you have purchased \n"
            << "| 5. View your balance \n"
            << "| 6. List the list of subsequent auction items \n"
            << "| 7. Search for an auction item \n"
            << "| 8. Give up the operation, the next user to operate \n"
            << "| Please choose the operation: \n"
            << "------------------------------------------------------------------------\n\n\n";
        std::cin >> choice;
        Tool::clearInput();

        int id;
        double bid;
        int searchMode;
        std::string name;
        std::string type;

        switch (choice) {

        case 1:
            currentItem.showBid();
            break;
        case 2:
            currentItem.showItem();
            break;
        case 3:
            std::cout << "Enter your bid: ";
            std::cin >> bid;
            user.bidItem(currentItem.Id, bid, items);
            Tool::pause();
            break;
        case 4:
            user.userOwnItems.showItems();
            break;
        case 5:
            user.getBudget();
            break;
        case 6:
            std::cout << "The list of subsequent auction items is as follows: " << std::endl;
            for (auto begin = items.begin(); begin != items.end(); ++begin) {
                begin->showItem();
            }
            break;
        case 7:
            Tool::clearScreen();
            std::cout << "Please enter the search mode:\n1 represents search by name\n2 represents search by id\n3 represents search by category: ";
            std::cin >> searchMode;
            switch (searchMode) {
            case 1:
                std::cout << "Please enter the name of the item to be searched: \n\n";
                std::cin >> name;
                items.displayItem(name);
                break;
            case 2:

                std::cout << "Please enter the id of the item to be searched: ";
                std::cin >> id;
                items.displayItem(id);
                break;
            case 3:
                std::cout << "Please enter the category of the item to be searched: ";
                std::cin >> type;
                items.displayItemsByType(type);
                break;
            default:
                std::cout << "Invalid search mode, please choose again" << std::endl;
                break;
            }
            Tool::pause();
            break;
        case 8:
            std::cout << "The next user operates\n";
            break;
        default:
            std::cout << "Invalid choice, please choose again\n";
            break;
        }
        Tool::pause();
    } while (choice != 8 && choice != 3);
    return choice;
}

void Auction::settleAuction(Item& item) {
    if (!item.bids.empty()) {
        Bid highestBid = *std::max_element(item.bids.begin(), item.bids.end(), [](const Bid& a, const Bid& b) {
            return a.price < b.price;
            });
        std::cout << "The item " << item.name << " was purchased by " << highestBid.user << " at a price of " << highestBid.price << std::endl;
        
        UserQueue::getItemOnAuction(highestBid, item, users);

        totalAmount += highestBid.price;  // Update total transaction price
    }
    else {
        std::cout << "No one bid for the item " << item.name << std::endl;
    }
    Tool::pause();
}


void Auction::showUserOwnItems(Auction auction) {
    std::map<int, std::vector<std::string>> userItemsMap;
    UserQueue users = auction.users;
    for (auto& user : users) {
        for (auto& item : user.userOwnItems) {
            userItemsMap[user.userOwnItems.size()].push_back(item.name);
        }
    }

    for (const auto& pair : userItemsMap) {
        const auto& itemCount = pair.first;
        const auto& itemNames = pair.second;
        for (const auto& userName : itemNames) {
            std::cout << "The number of items owned by the user " << userName << " is: " << itemCount << std::endl << " The items owned are as follows: " << std::endl;
            for (const auto& itemName : itemNames) {
                std::cout << itemName << "\t";
            }
            std::cout << std::endl;
        }
    }
}

void Auction::showUserOwnItems() {
    std::map<int, std::vector<std::string>> userItemsMap;
    for (auto& user : users) {
        for (auto& item : user.userOwnItems) {
            userItemsMap[user.userOwnItems.size()].push_back(item.name);
        }
    }

    for (const auto& pair : userItemsMap) {
        const auto& itemCount = pair.first;
        const auto& itemNames = pair.second;
        for (const auto& userName : itemNames) {
            std::cout << "The number of items owned by the user " << userName << " is: " << itemCount << std::endl << " The items owned are as follows: " << std::endl;
            for (const auto& itemName : itemNames) {
                std::cout << itemName << "\t";
            }
            std::cout << std::endl;
        }
    }
}



int Auction::getItemsCount() {
    return items.size();
}

int Auction::getBiddedCount() {
    return bidCount;
}

double Auction::getTotalAmount() {
    return totalAmount;
}

std::string Auction::getDate() const {
    return auctionDate;
}

std::string Auction::getName() const {
    return auctionName;
}
void Auction::saveAuction() {
    std::string filename = auctionName + ".auction";
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    outFile << auctionName << "\n";
    outFile << auctionDate << "\n";
    outFile << totalAmount << "\n";

    // 存储 auction.items （不调用函数）
    outFile << items.size() << "\n";
    for (const Item& item : items) {
        outFile << item.Id << "\n";
        outFile << item.name << "\n";
        outFile << item.condition << "\n";
        outFile << item.description << "\n";
        outFile << item.estimatedValue << "\n";
        outFile << item.types.size() << "\n";
        for (const std::string& type : item.types) {
            outFile << type << "\n";
        }
        outFile << item.bids.size() << "\n";
        for (const Bid& bid : item.bids) {
            outFile << bid.user << "\n";
            outFile << bid.price << "\n";
        }

        // 存储 auction.users （不调用函数）
        outFile << users.size() << "\n";
        for (User& user : users) {
            outFile << user.name << "\n";
            outFile << user.budget << "\n";
            outFile << user.userOwnItems.size() << "\n";
            for (Item& item : user.userOwnItems) {
                outFile << item.Id << "\n";
                outFile << item.name << "\n";
                outFile << item.condition << "\n";
                outFile << item.description << "\n";
                outFile << item.estimatedValue << "\n";
                outFile << item.types.size() << "\n";
                for (const std::string& type : item.types) {
                    outFile << type << "\n";
                }
                outFile << item.bids.size() << "\n";
                for (const Bid& bid : item.bids) {
                    outFile << bid.user << "\n";
                    outFile << bid.price << "\n";
                }
            }
        }
        std::cout << "Auction saved successfully" << std::endl;
        Tool::pause();
        Tool::clearScreen();
    }

    outFile.close();
}
void Auction::loadAuction(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        Tool::pause();
        return;
    }

    std::getline(inFile, auctionName);
    std::cout << "Auction name loaded successfully." << std::endl;

    std::getline(inFile, auctionDate);
    std::cout << "Auction date loaded successfully." << std::endl;

    inFile >> totalAmount;
    inFile.ignore();
    std::cout << "Total amount loaded successfully." << std::endl;

    size_t size;
    inFile >> size;
    inFile.ignore();
    
    for (size_t i = 0; i < size; ++i) {
        Item item;
        inFile >> item.Id;
        std::cout << "Item ID loaded successfully." << std::endl;

        std::getline(inFile, item.name);
        std::cout << "Item name loaded successfully." << std::endl;

        std::getline(inFile, item.condition);
        std::cout << "Item condition loaded successfully." << std::endl;

        std::getline(inFile, item.description);
        std::cout << "Item description loaded successfully." << std::endl;

        inFile >> item.estimatedValue;
        inFile.ignore();
        std::cout << "Item estimated value loaded successfully." << std::endl;

        size_t typeSize;
        inFile >> typeSize;
        inFile.ignore();
        typeSize = 3;
        
        // 检查是否到达文件结束或者typeSize是否过大
        if (inFile.eof() || typeSize > MAX_TYPE_SIZE) {
            std::cout << "-" << typeSize << "-" << std::endl;
            std::cerr << "Invalid type size or unexpected end of file." << std::endl;
            Tool::pause();
            return;
        }
        
        for (size_t j = 0; j < typeSize; ++j) {
            std::string type;
            std::getline(inFile, type);
        
            // 检查是否到达文件结束
            if (inFile.eof()) {
                std::cerr << "Unexpected end of file when reading types." << std::endl;
                Tool::pause();
                return;
            }
        
            item.types.push_back(type);
        }
        std::cout << "Item types loaded successfully." << std::endl;
        std::cout << "Item bids loaded successfully." << std::endl;

        items.addItem(item);
    }
    std::cout << "All items loaded successfully." << std::endl;

    inFile >> size;
    inFile.ignore();
    for (size_t i = 0; i < size; ++i) {
        User user;
        std::getline(inFile, user.name);
        std::cout << "User name loaded successfully." << std::endl;

        inFile >> user.budget;
        inFile.ignore();
        std::cout << "User budget loaded successfully." << std::endl;

        size_t itemSize;
        inFile >> itemSize;
        inFile.ignore();

        for (size_t j = 0; j < itemSize; ++j) {
            Item item;
            inFile >> item.Id;
            std::cout << "User item ID loaded successfully." << std::endl;

            std::getline(inFile, item.name);
            std::cout << "User item name loaded successfully." << std::endl;

            std::getline(inFile, item.condition);
            std::cout << "User item condition loaded successfully." << std::endl;

            std::getline(inFile, item.description);
            std::cout << "User item description loaded successfully." << std::endl;

            inFile >> item.estimatedValue;
            inFile.ignore();
            std::cout << "User item estimated value loaded successfully." << std::endl;

            size_t typeSize;
            inFile >> typeSize;
            inFile.ignore();

            typeSize = 3;

            if (inFile.eof() || typeSize > MAX_TYPE_SIZE) {
                std::cout << "-" << typeSize << "-" << std::endl;

                std::cerr << "Invalid type size or unexpected end of file." << std::endl;
                Tool::pause();
                return;
            }
            for (size_t k = 0; k < typeSize; ++k) {
                std::string type;
                std::getline(inFile, type);
                if (inFile.eof()) {
                    std::cerr << "Unexpected end of file when reading types." << std::endl;
                    Tool::pause();
                    return;
                }
                item.types.push_back(type);
            }
            std::cout << "User item types loaded successfully." << std::endl;

            size_t bidSize;
            inFile >> bidSize;
            inFile.ignore();
            if (inFile.eof() || bidSize > MAX_BID_SIZE) {
                std::cerr << "Invalid bid size or unexpected end of file." << std::endl;
                Tool::pause();
                return;
            }
            for (size_t k = 0; k < bidSize; ++k) {
                Bid bid;
                std::getline(inFile, bid.user);
                inFile >> bid.price;
                inFile.ignore();
                if (inFile.eof()) {
                    std::cerr << "Unexpected end of file when reading bids." << std::endl;
                    Tool::pause();
                    return;
                }
                item.bids.push_back(bid);
            }
            std::cout << "User item bids loaded successfully." << std::endl;

            user.userOwnItems.addItem(item);
        }
        std::cout << "All user items loaded successfully." << std::endl;

        users.addUser(user);
    }
    std::cout << "All users loaded successfully." << std::endl;

    inFile.close();
    std::cout << "Auction loaded successfully." << std::endl;
}