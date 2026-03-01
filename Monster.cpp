#include "Monster.h"

Monster::Monster (const std::string& name, const int hp)
    : _name(name), _hp(hp), _maxHp(hp)
    {}

void Monster::takeDamage (const int dmg) {
    _hp -= dmg;
    std::cout << _name << " 受到了 " << dmg << " 点伤害! ";
    if (_hp <= 0 ) {
        _hp = 0;
        std::cout << "它倒下了！";
    }
    std::cout << "剩余HP " << _hp << " / " << _maxHp << std::endl;
}

bool Monster::isAlive () const {
    return _hp > 0;
}

std::string Monster::getName () const {
    return _name;
}

std::ostream& operator << (std::ostream& os, Monster& monster) {
    os << ">> " << monster._name << std::endl;
    os << "生命值：" << monster._hp << " / " << monster._maxHp << std::endl;
    return os;
}