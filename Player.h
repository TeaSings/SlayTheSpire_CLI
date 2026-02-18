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
    Player (const int mana = 0)
    : _mana(mana)
    {}

    void drawCard (Card*& card) {
        handCards.push_back(card);
    }

    void playAllCards () {
        for (size_t i = 0; i < handCards.size(); ) {
            if (handCards[i]->getCost() <= _mana) {
                handCards[i]->play();
                _mana -= handCards[i]->getCost();
                delete handCards[i];
                handCards.erase(handCards.begin() + i);
            } else {
                std::cout << "当前能量不足" << std::endl;
                i++;
            }
        }
        std::cout << "所有牌已出完" << std::endl;
    }
};

#endif