#include "auction.h"
#include "option.h"
#include "tool.h"
#include "test.h"
#define DEBUG 0
int main() {
    if (DEBUG) {
        testCase1();
    }
    else {
        std::cout << "\t\t\tWelcome to the Auction System\n\n";
        std::cout << "\tversion: 1.1.7" << std::endl;
        std::cout << "\tedited by KevinYoung, Soft Engineering, 20222410123" << std::endl;
        std::cout << "\tc++11 Standard library\n\n";

        Tool::pause();
        Tool::clearScreen();
        Option option;
        int choice;
        do {
            std::cout << "\t\tCurrent Auction:" << option.getName() << " " << option.getDate() << std::endl;
            std::cout << "\n\n\n";
            std::cout << "\t\tMain Menu\n";
            std::cout << "\t\t\t1. Create and save an auction\n";
            std::cout << "\t\t\t2. Load an auction from file\n";
            std::cout << "\t\t\t3. Start auction\n";
            std::cout << "\t\t\t4. Exit\n\n\n";
            std::cout << "\t\tEnter your choice: ";
            std::cin >> choice;
            switch (choice) {
            case 1:
                option.createAndSaveAuction();
                break;
            case 2:
                option.loadAuctionFromFile();
                break;
            case 3:
                option.startAuction();
                break;
            case 4:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
                Tool::pause();
            }
        } while (choice != 4);
    }
    return 0;
}