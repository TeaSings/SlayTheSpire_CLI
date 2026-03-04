#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>
#include <string>

class Monster;

class Player {
private:
    std::vector<std::unique_ptr<Card>> _drawPile; //三个vector分别用来表示: 弃牌堆 手牌 抽牌堆
    std::vector<std::unique_ptr<Card>> _handCards;
    std::vector<std::unique_ptr<Card>> _discardPile;
    int _hp, _mana, _shield;
public:
    Player (const int hp = 0, const int mana = 0, const int shield = 0);
    ~Player ();

    bool isAlive() const;
    void initDeck ();
    void drawCard (int count = 1);
    void takeTurn (Monster& monster);// 全新的开始回合函数，正式步入可交互的游戏
    void takeDamage (const int dmg);
    void getShield (const int shield);
    void resetShield ();
    void endTurn ();
    void shuffle ();
    friend std::ostream& operator << (std::ostream& os, const Player& player);
};

#endif