#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>
#include <string>

class Monster;

class Player {
private:
    std::vector<std::unique_ptr<Card>> handCards;
    int _hp, _mana, _shield;
public:
    Player (const int hp = 0, const int mana = 0, const int shield = 0);
    ~Player ();

    void drawCard (std::unique_ptr<Card> card);
    void playAllCards (Monster& monster);
    void takeDamage (const int dmg);
    void getShield (const int shield);
    void resetShield ();
};

#endif