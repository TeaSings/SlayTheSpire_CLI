#ifndef CONCRETEMONSTERS_H
#define CONCRETEMONSTERS_H

#include "Monster.h"
#include "Player.h"
#include <cstdlib>

class JawWorm :public Monster {
public:
    JawWorm (const std::string& name = "", const int hp = 0)
    : Monster(name, hp)
    {} 

    virtual std::unique_ptr<Monster> clone () const override {
        return std::make_unique<JawWorm>(*this);
    }

    virtual void takeAction (Player& player) override {
        if (_intentType == Attack) {
            std::cout << ">> " << _name << " 发起了撕咬" << std::endl;
            player.takeDamage(_intentValue);
        } else if (_intentType == Defend) {
            std::cout << ">> " << _name << " 进行了格挡" << std::endl;
            getShield(_intentValue);
        }
        reduceStatusEffectDuration();
        rollIntent();
    }

    virtual void rollIntent () override {
        int random = std::rand() % 2;
        if (random == 0) {
            _intentType = Attack;
            _intentValue = 11;
        } else {
            _intentType = Defend;
            _intentValue = 6;
        }
    }
};

#endif