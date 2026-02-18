#include "Player.h"

Player::Player (const int mana)
    : _mana(mana)
    {}

Player::~Player () {
    for (auto x : handCards) delete x;
}

void Player::drawCard (Card*& card) {
    handCards.push_back(card);
}

void Player::playAllCards () {
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