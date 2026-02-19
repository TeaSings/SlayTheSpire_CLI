#include "Player.h"
#include "Monster.h"

Player::Player (const int hp, const int mana, const int shield)
    : _hp(hp), _mana(mana), _shield(shield)
    {}

Player::~Player () {
    for (auto x : handCards) delete x;
}

void Player::drawCard (Card*& card) {
    handCards.push_back(card);
}

void Player::playAllCards (Monster& monster) {
    for (size_t i = 0; i < handCards.size(); ) {
        if (handCards[i]->getCost() <= _mana) {
            handCards[i]->play(*this, monster);
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

void Player::takeDamage (const int dmg) {
    int currDmg = dmg;
    if (_shield >= dmg) {
        _shield -= dmg;
        currDmg = 0;
        std::cout << "角色格挡了 " << dmg << " 点伤害" << std::endl;
    } else {
        if (_shield > 0) std::cout << "角色格挡了 " << _shield << " 点伤害" << std::endl;
        currDmg -= _shield;
        _shield = 0;
    }

    if (currDmg > 0) {
        std::cout << "角色承受了 " << currDmg << " 点伤害" << std::endl;
        if (_hp > currDmg) {
            _hp -= currDmg;
            std::cout << "角色剩余生命值 " << _hp << std::endl;
        } else {
            std::cout << "角色死亡" << std::endl;
            _hp = 0;
        }
    }
}

void Player::getShield (const int shield) {
    _shield += shield;
    std::cout << "角色获得了 " << shield << " 点格挡,当前总格挡为 "<< _shield << std::endl;
}

void Player::resetShield () {
    _shield = 0;
    std::cout << "回合结束,角色防御清空" << std::endl;
}