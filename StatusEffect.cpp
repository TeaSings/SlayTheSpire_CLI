#include "StatusEffect.h"

StatusEffect::StatusEffect (const int duration)
: _duration(duration)
{}

StatusEffect::~StatusEffect () {};

bool StatusEffect::isExpired () const {
    return _duration <= 0;
}

void StatusEffect::reduceDuration () {
    if (_duration > 0) _duration --;
}