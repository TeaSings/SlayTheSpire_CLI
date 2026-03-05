#include "Monster.h"
#include "StatusEffect.h"

std::map<std::string, std::unique_ptr<Monster>> MonsterLibrary::monsterLibrary;

Monster::Monster (const Monster& other)
    : _name(other._name), _hp(other._hp), _maxHp(other._maxHp), _intentValue(other._intentValue), _shield(other._shield), _intentType(other._intentType)
    {}

Monster::Monster (const std::string& name, const int hp)
    : _name(name), _hp(hp), _maxHp(hp), _intentValue(0), _shield(0), _intentType(Attack)
    {}

void Monster::takeDamage (const int dmg) {
    int finalDamage = dmg;
    for (const auto& effect : _statusEffects) {
        finalDamage = effect->modifyDamageTaken(finalDamage);
    }

    if (_shield > finalDamage) {
        _shield -= finalDamage;
        std::cout << _name << " 格挡了 " << finalDamage << " 点伤害" << std::endl;
        finalDamage = 0;
    } else {
        if (_shield > 0) std::cout << _name << " 格挡了" << _shield << " 点伤害" << std::endl;
        finalDamage -= _shield;
        _shield = 0;
    }

    if (finalDamage > 0) {
        std::cout << _name << " 承受了 " << finalDamage << " 点伤害" << std::endl;
        _hp -= finalDamage;
    }

    if (_hp <= 0 ) {
        _hp = 0;
        std::cout << "它倒下了！";
    }
    if (_hp > 0) std::cout << "剩余HP " << _hp << " / " << _maxHp << std::endl;
}

void Monster::getShield (const int shield) {
    _shield += shield;
    std::cout << _name << " 获得了 " << shield << " 点格挡" << std::endl;
}

bool Monster::isAlive () const {
    return _hp > 0;
}

void Monster::applyStatusEffect (std::unique_ptr<StatusEffect> effect) {
    _statusEffects.push_back(std::move(effect));
}

void Monster::reduceStatusEffectDuration () {
    if (!_statusEffects.empty()) {
        std::cout << ">> " << _name << " 的状态减少 1 回合" << std::endl;
    }
    for (auto& effect : _statusEffects) {
        effect->reduceDuration();
    }
    for (auto effect = _statusEffects.begin(); effect != _statusEffects.end();) {
        if ((*effect)->isExpired()) {
            effect = _statusEffects.erase(effect);
        } else {
            effect++;
        }
    }
}

int Monster::getIntentValue () const {
    return _intentValue;
}

std::string Monster::getIntentText () const {
    if (_intentType == Attack) return "攻击 " + std::to_string(_intentValue);
    else if (_intentType == Defend) return "防御 " + std::to_string(_intentValue);
    return "[Warning]: 未知意图";
}

MonsterIntentType Monster::getIntentType () const {
    return _intentType;
}

std::ostream& operator << (std::ostream& os, Monster& monster) {
    os << ">> " << monster._name << std::endl;
    os << "生命值: " << monster._hp << " / " << monster._maxHp << std::endl;
    os << "格挡值: " << monster._shield << std::endl;
    os << "当前意图: " << monster.getIntentText() << std::endl;
    if (!monster._statusEffects.empty()) {
        os << "状态效果: ";
        for (const auto& effect : monster._statusEffects) {
            os << effect->getStatusEffectName() << std::endl;
        }
    }
    return os;
}

void MonsterLibrary::registerMonster (const std::string& monsterName, std::unique_ptr<Monster> monsterPointer) {
    if (monsterLibrary.find(monsterName) == monsterLibrary.end()) {
        monsterLibrary[monsterName] = std::move(monsterPointer);
    } else {
        std::cout << "[Warning]: 当前怪物已存在于怪物图鉴中,加入失败。" << std::endl;
    }
}

std::unique_ptr<Monster> MonsterLibrary::createMonster (const std::string& monsterName) {
    if (monsterLibrary.find(monsterName) != monsterLibrary.end()) {
        return monsterLibrary[monsterName]->clone();
    } else {
        std::cout << "[Warning]: 当前怪物在怪物图鉴中未找到,克隆失败" << std::endl;
        return nullptr;
    }
}