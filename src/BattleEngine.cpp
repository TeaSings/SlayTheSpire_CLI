#include "BattleEngine.h"
#include "Monster.h"
#include "Player.h"

void BattleEngine::startBattle (Player& player, Monster& monster) {
    while (player.isAlive() && monster.isAlive()) {
        player.takeTurn(monster);
    }
}

void BattleEngine::startPlayerTurn (Player& player, Monster& monster) {
    
}
