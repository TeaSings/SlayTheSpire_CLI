#ifndef STATUSEFFECT_H
#define STATUSEFFECT_H

#include <string>

class StatusEffect {
protected:
    int _duration;
public:
    StatusEffect (int duration = 0);
    virtual ~StatusEffect ();

    bool isExpired () const;
    void reduceDuration ();
    virtual std::string getStatusEffectName () const = 0;
    virtual int modifyDamageTaken (int incommingDamage) { return incommingDamage; };
};

#endif