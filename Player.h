#ifndef PLAYER_H
#define PLAYER_H

#include "ConcreteCards.h"
#include <vector>
#include <string>

class Player {
private:
    std::vector<Card*> handCards;
    int _mana;
public:
    Player (const int mana = 0);
    ~Player ();

    void drawCard (Card*& card);

    void playAllCards ();
};

#endif