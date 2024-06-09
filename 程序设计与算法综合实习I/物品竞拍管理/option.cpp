#include "Option.h"
#include "tool.h"
#include "test.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>

Option::Option() : auction(nullptr) {}

Option::~Option() { delete auction; }

void Option::createAndSaveAuction() {
    delete auction;
    auction = new Auction();
    std::cout << "Creating a new auction...\n";
    Tool::clearInput();
    Tool::pause();

    auction->InitAuction();

    auction->saveAuction();
    std::cout << "Auction saved to" << auction->getName() << ".auction\n";
    
    Tool::pause();
    Tool::clearScreen();
    delete auction;
    auction = nullptr;
}

void Option::loadAuctionFromFile() {
    std::vector<std::string> files;
    std::string path = ".\\*.auction";
    std::cout << path << std::endl;
    Tool::pause();

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

    int choice;
    do {
        std::cout << "Select an auction file:\n";
        for (size_t i = 0; i < files.size(); ++i) {
            std::cout << i + 1 << ". " << files[i] << "\n";
        }
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        --choice;
        Tool::clearScreen();
    } while (choice < 0 || choice >= files.size());

    delete auction;
    auction = new Auction();
    auction->loadAuction(files[choice]);
    std::cout << "Auction loaded from " << files[choice] << "\n";
    Tool::pause();
    Tool::clearScreen();
    if (auction) {
        std::cout << "Auction loaded successfully.\n";
        std::cout << "Here is the auction information:\n";
        Tool::pause();
        Tool::clearScreen();

        auction->showAuction();
    }

}

void Option::startAuction() {
     if (auction == nullptr) {
         std::cout << "No auction loaded.\n";
         Tool::pause();
         Tool::clearScreen();
         return;
     }
     std::cout << "Starting auction...\n";
     Tool::pause();
     Tool::clearScreen();
     testCase2();
}

std::string Option::getName() {
    if (auction == nullptr) {
        return "No auction loaded";
        Tool::clearScreen();
    }
    return auction->getName();
}

std::string Option::getDate() {
    if (auction == nullptr) {
        return "";
    }
    return auction->getDate();
}

// void Option::modifyAuction() {
//     if (auction == nullptr) {
//         std::cout << "No auction loaded.\n";
//         Tool::pause();
//         return;
//     }
//     // 请输入你要修改的内容，选择修改拍卖会信息、拍卖物品、拍卖用户...
//     // 1. 修改拍卖会信息
//     // 2. 修改拍卖物品
//     // 3. 修改拍卖用户
//     // 4. 返回
//     // ...
// }