#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>

class Monster {
private:
    std::string _name;
    int _hp;
    int _maxHp;

public:
    Monster (const std::string& name = "", const int hp = 0);

    void takeDamage (const int dmg);
    bool isAlive () const;
    void printStatus () const;
    std::string getName () const;
};

#endif