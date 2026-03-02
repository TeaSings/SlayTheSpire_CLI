#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
#include <map>
#include <memory>

class Player;

class Monster {
protected:
    std::string _name;
    int _hp;
    int _maxHp;
    Monster (const Monster& other) = default;

public:
    Monster (const std::string& name = "", const int hp = 0);
    virtual ~Monster () {};

    void takeDamage (const int dmg);
    bool isAlive () const;
    std::string getName () const;
    virtual void takeAction (Player& player) = 0;
    virtual std::unique_ptr<Monster> clone () const = 0;
    friend std::ostream& operator << (std::ostream& os, Monster& monster);
};

class MonsterLibrary {
private:
    static std::map<std::string, std::unique_ptr<Monster>> monsterLibrary;
public:
    static void registerMonster (const std::string& monsterName, std::unique_ptr<Monster> monsterPointer);
    static std::unique_ptr<Monster> createMonster (const std::string& monsterName);
};

#endif