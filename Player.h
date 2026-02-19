#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>
#include <string>

class Monster;

class Player {
private:
    std::vector<Card*> handCards;
    int _mana;
public:
    Player (const int mana = 0);
    ~Player ();

    void drawCard (Card*& card);

    void playAllCards (Monster& monster);
};

#endif