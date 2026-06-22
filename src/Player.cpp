#include "Player.h"
#include "Monster.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <limits>

Player::Player (const int hp, const int mana, const int shield)
    : _hp(hp), _mana(mana), _shield(shield)
    {}

Player::~Player () {}

bool Player::isAlive () const {
    return _hp > 0;
}

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

void Player::takeTurn (Monster& monster) {
    std::cout << "输入 0 以结束当前回合" << std::endl;
    drawCard(5);
    while (1) {
        if (!isAlive()) {
            std::cout << "玩家已死亡" << std::endl;
            break;
        }

        std::cout << *this;
        std::cout << monster;
        int choice = -1;
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                std::cout << "检测到输入结束, 回合终止。" << std::endl;
                break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入无效, 请输入正确的数字" << std::endl;
            continue;
        }

        if (choice == 0) break;

        if (choice < 1 || choice > _handCards.size()) {
            std::cout << "请输入有效的手牌编号 (1 - " << _handCards.size() << ")" << std::endl;
            continue;
        }

        if (_handCards[choice - 1]->getCost() > _mana) {
            std::cout << "当前能量不足" << std::endl;
            continue;
        }

        _handCards[choice - 1]->play(*this, monster);
        _mana -= _handCards[choice - 1]->getCost();
        _discardPile.push_back(std::move(_handCards[choice - 1]));
        _handCards.erase(_handCards.begin() + choice - 1);

        if (!monster.isAlive()) {
            std::cout << "怪物已被击败！游戏结束" << std::endl;
            break;
        }

        if (_handCards.empty()) {
            std::cout << "手牌已打完, 回合结束" << std::endl;
            break;
        }
    }
    if(monster.isAlive() && isAlive()) {
            monster.takeAction(*this);
    }
    endTurn();
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

std::ostream& operator << (std::ostream& os, const Player& player) {
    os << ">> Player: " << std::endl;
    os << "生命值: " << player._hp << std::endl;
    os << "能量值: " << player._mana << std::endl;
    os << "格挡值: " << player._shield << std::endl;
    os << "当前手牌: " << std::endl;
    if (player._handCards.empty()) {
        os << "(空)" << std::endl;
    } else {
        os << "  手牌总数: " << player._handCards.size() << std::endl;
        for (size_t i = 0; i < player._handCards.size(); i++) {
            os << "  " << (i + 1) << ". ";
            os << *player._handCards[i];
            if (i != player._handCards.size()) {
                os << std::endl;
            }
        }
    }
    return os;
}