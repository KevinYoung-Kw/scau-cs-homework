#include "test.h"
#include <iostream>

void testCase1() {
    Auction auction;
    
    ItemList items = {
        Item("item1", "Great", "A test item", 100, {"A", "B", "C"}),
        Item("item2", "Good", "Another test item", 200, {"D", "B", "F"}),
        Item("item3", "Bad", "Yet another test item", 300, {"A", "H", "C"})

    };

    UserQueue users = {
        User("user1", 200),
        User("user2", 300),
    };

    auction.InitAuction("Auction1", "2024-05-06");
    auction.InitItem(items);
    auction.InitUser(users);

    auction.showAuction();
    auction.start();
    auction.showUserOwnItems();

}

void testCase2() {
/* testCase2 数据来源 ：
GameAuction
20240518
0
3
1
Gamshin:Impact
Great
Video game for Software Engineering
150
3
online
game
ER CI Yuan
0
2
Kevin
300
0
Gao Ziheng
200
0
2
CounterStrike
Good
FPS game for BUSHI GEMEN
100
3
game
online
gun
0
2
Kevin
300
0
Gao Ziheng
200
0
3
HeartStone
bad
A card game
50
3
game
card
Warcraft
0
2
Kevin
300
0
Gao Ziheng
200
0

*/
    Auction auction;
    
    ItemList items = {
        Item("Gamshin:Impact", "Great", "Video game for Software Engineering", 150, {"online", "game", "ER CI Yuan"}),
        Item("CounterStrike", "Good", "FPS game for BUSHI GEMEN", 100, {"game", "online", "gun"}),
        Item("HeartStone", "bad", "A card game", 50, {"game", "card", "Warcraft"})
    };

    UserQueue users = {
        User("Kevin", 300),
        User("Gao Ziheng", 200),
    };

    auction.InitAuction("GameAuction", "2024-05-18");
    auction.InitItem(items);
    auction.InitUser(users);

    auction.showAuction();
    auction.start();
    auction.showUserOwnItems();

}