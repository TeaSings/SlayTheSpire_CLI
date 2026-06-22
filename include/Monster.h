#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include "StatusEffect.h"

class Player;

enum MonsterIntentType {
    Attack,
    Defend  
};

class Monster {
protected:
    std::string _name;
    int _hp;
    int _maxHp;
    int _intentValue;
    int _shield;
    MonsterIntentType _intentType;
    std::vector<std::unique_ptr<StatusEffect>> _statusEffects;

    Monster (const Monster& other);

public:
    Monster (const std::string& name = "", const int hp = 0);
    virtual ~Monster () {};

    void takeDamage (const int dmg);
    void getShield (const int shield);
    bool isAlive () const;
    void applyStatusEffect (std::unique_ptr<StatusEffect> effect);
    void reduceStatusEffectDuration ();
    int getIntentValue () const;
    std::string getIntentText () const;
    MonsterIntentType getIntentType () const;
    virtual void takeAction (Player& player) = 0;
    virtual std::unique_ptr<Monster> clone () const = 0;
    virtual void rollIntent () = 0;
    friend std::ostream& operator << (std::ostream& os, Monster& monster);
};

// 采用原型设计，使得怪物能够像卡牌一样采用相同逻辑进行生成
class MonsterLibrary {
private:
    static std::map<std::string, std::unique_ptr<Monster>> monsterLibrary;
public:
    static void registerMonster (const std::string& monsterName, std::unique_ptr<Monster> monsterPointer);
    static std::unique_ptr<Monster> createMonster (const std::string& monsterName);
};

#endif