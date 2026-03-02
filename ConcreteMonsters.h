#ifndef CONCRETEMONSTERS_H
#define CONCRETEMONSTERS_H

#include "Monster.h"
#include "Player.h"

class JawWorm :public Monster {
public:
    JawWorm (const std::string& name = "", const int hp = 0)
    : Monster(name, hp)
    {} 

    virtual std::unique_ptr<Monster> clone () const override {
        return std::make_unique<JawWorm>(*this);
    }

    virtual void takeAction (Player& player) override {
        std::cout << ">> " << _name << " 发起了撕咬！" << std::endl;
        player.takeDamage(11);
    }
};

#endif