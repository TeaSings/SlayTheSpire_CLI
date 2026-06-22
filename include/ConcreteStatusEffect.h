#ifndef CONCRETESTATUSEFFECT_H
#define CONCRETESTATUSEFFECT_H

#include "StatusEffect.h"
#include "Player.h"
#include "Monster.h"

class VulnerableEffect :public StatusEffect {
public:
    VulnerableEffect (int duration = 0)
    : StatusEffect(duration)
    {}
    
    virtual std::string getStatusEffectName () const override {
        return "易伤";
    }

    virtual int modifyDamageTaken (int incommingDamage) override {
        return incommingDamage * 1.5;
    }
};

#endif