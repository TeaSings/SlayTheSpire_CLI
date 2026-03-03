#ifndef CONCRETECARDS_H
#define CONCRETECARDS_H

#include "Card.h"
#include "Monster.h"
#include "Player.h"
#include "ConcreteStatusEffect.h"

class StrikeCard :public Card {
public:
    StrikeCard (const std::string& name = "", const int cost = 0)
    : Card(name, cost)
    {}

    virtual void play (Player& player, Monster& monster) override {
        monster.takeDamage(6);
    }

    virtual std::unique_ptr<Card> clone () const override {
        return std::make_unique<StrikeCard>(*this);
    }

    virtual void print (std::ostream& os) const override {
        os << ">> 打击" << std::endl;
        os << "消耗 1 点能量" << std::endl;
        os << "造成 6 点伤害" << std::endl;
    }

};

class DefendCard :public Card {
public:
    DefendCard (const std::string& name = "", const int cost = 0)
    : Card(name, cost)
    {}

    virtual void play (Player& player, Monster& monster) override {
        player.getShield(5);
    }

    virtual std::unique_ptr<Card> clone () const override {
        return std::make_unique<DefendCard>(*this);
    }

    virtual void print (std::ostream& os) const override {
        os << ">> 防御" << std::endl;
        os << "获得 5 点格挡" << std::endl;
    }
};

class BashCard :public Card {
public:
    BashCard (const std::string& name = "", const int cost = 0)
    : Card(name, cost)
    {}

    virtual void play(Player& player, Monster& monster) override {
        monster.takeDamage(8);
        monster.applyStatusEffect(std::make_unique<VulnerableEffect>(2));
    }

    virtual std::unique_ptr<Card> clone () const override {
        return std::make_unique<BashCard>(*this);
    }

    virtual void print (std::ostream& os) const override {
        os << ">> 痛击" << std::endl;
        os << "造成 8 点伤害" << std::endl;
        os << "使目标获得 2 点易伤" << std::endl;
    }
};

#endif