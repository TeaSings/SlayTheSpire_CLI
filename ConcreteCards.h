#ifndef CARD_BASIC_H
#define CARD_BASIC_H

#include "Card.h"
#include "Monster.h"
#include "Player.h"

class StrikeCard :public Card {
public:
    StrikeCard (const std::string& name = "", const int cost = 0)
    : Card(name, cost)
    {}

    virtual void play (Player& player, Monster& monster) override {
        std::cout << ">> 使用了打击" << std::endl;
        monster.takeDamage(6);
        std::cout << "对 " << monster.getName() << " 造成 6 点伤害"<< std::endl;
    }

    virtual std::unique_ptr<Card> clone () const override {
        return std::make_unique<StrikeCard>(*this);
    }
};

class DefendCard :public Card {
public:
    DefendCard (const std::string& name = "", const int cost = 0)
    : Card(name, cost)
    {}

    virtual void play (Player& player, Monster& monster) override {
        std::cout << ">> 使用了防御" << std::endl;
        player.getShield(5);
    }

    virtual std::unique_ptr<Card> clone () const override {
        return std::make_unique<DefendCard>(*this);
    }
};

class BashCard :public Card {
public:
    BashCard (const std::string& name = "", const int cost = 0)
    : Card(name, cost)
    {}

    virtual void play(Player& player, Monster& monster) override {
        std::cout << ">>使用了痛击" << std::endl;
        monster.takeDamage(8);
        std::cout << "对 " << monster.getName() << " 造成 8 点伤害"<< std::endl;
    }

    virtual std::unique_ptr<Card> clone () const override {
        return std::make_unique<BashCard>(*this);
    }
};

#endif