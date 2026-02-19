#include "Player.h"
#include "Monster.h"
#include <algorithm>
#include <random>
#include <chrono>

Player::Player (const int hp, const int mana, const int shield)
    : _hp(hp), _mana(mana), _shield(shield)
    {}

Player::~Player () {}

void Player::initDeck () {
    for (int i = 0; i < 5; i++) _drawPile.push_back(CardLibrary::createCard("打击"));
    for (int i = 0; i < 4; i++) _drawPile.push_back(CardLibrary::createCard("防御"));
    _drawPile.push_back(CardLibrary::createCard("痛击"));

    shuffle();
}

void Player::shuffle () {
    for (auto& card : _discardPile) {
        _drawPile.push_back(std::move(card));
    }
    _discardPile.clear();

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(_drawPile.begin(), _drawPile.end(), std::default_random_engine(seed));
    
    std::cout << "洗牌完成！当前抽牌堆有 " << _drawPile.size() << " 张牌。" << std::endl;
}

void Player::drawCard (int count) {
    for (int i = 0; i < count; i++) {
        if (_drawPile.empty()) {
            if (_discardPile.empty()) {
                std::cout << "抽牌堆和弃牌堆都没牌了！" << std::endl;
                break;
            }
            shuffle();
        }
        
        _handCards.push_back(std::move(_drawPile.back()));
        _drawPile.pop_back();
    }
}

void Player::endTurn () {
    for (auto& card : _handCards) {
        _discardPile.push_back(std::move(card));
    }
    _handCards.clear();

    resetShield();
    _mana = 3;
    std::cout << "--- 玩家回合结束 ---" << std::endl;
}

void Player::playAllCards (Monster& monster) {
    for (size_t i = 0; i < _handCards.size(); ) {
        if (_handCards[i]->getCost() <= _mana) {
            _handCards[i]->play(*this, monster);
            _mana -= _handCards[i]->getCost();
            _discardPile.push_back(std::move(_handCards[i]));
            _handCards.erase(_handCards.begin() + i);
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