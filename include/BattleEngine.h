#ifndef BATTLEENGINE_H
#define BATTLEENGINE_H

#include <iostream>

class Player;
class Monster;

class BattleEngine {
public:
    void startBattle (Player& player, Monster& monster);
    void startPlayerTurn (Player& player, Monster& monster);
    void startMonsterTurn (Player& player, Monster& monster);
};

#endif