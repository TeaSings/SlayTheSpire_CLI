#include "ConcreteCards.h"
#include "Player.h"
#include "ConcreteMonsters.h"

int main() {
    system("chcp 65001");
    
    // 1. 注册卡牌原型（只注册一次，后续都通过图鉴 clone）
    CardLibrary::registerCard("打击", std::make_unique<StrikeCard>(StrikeCard("打击", 1)));
    CardLibrary::registerCard("防御", std::make_unique<DefendCard>(DefendCard("防御", 1)));
    CardLibrary::registerCard("痛击", std::make_unique<BashCard>(BashCard("痛击", 2)));
    
    MonsterLibrary::registerMonster("大颚虫", std::make_unique<JawWorm>(JawWorm("大颚虫", 40)));
    // 2. 创建玩家和怪物
    Player ironclad(70, 3, 0); 
    std::unique_ptr<Monster> jawWormPtr = MonsterLibrary::createMonster("大颚虫");
    Monster& jawWorm = *jawWormPtr;

    std::cout << ironclad << "\n" <<jawWorm << std::endl;
    // 3. 初始化卡组 (会自动生成 5打击 4防御 1痛击 并进行首次洗牌)
    std::cout << "========== 游戏初始化 ==========" << std::endl;
    ironclad.initDeck();

    // 4. 模拟游戏主循环 (我们测试模拟 3 个回合)
    std::cout << "\n========== 战斗开始 ==========" << std::endl;

    while (jawWorm.isAlive()) {
        ironclad.takeTurn(jawWorm);
    }

    std::cout << "\n========== 战斗结束 ==========" << std::endl;
    
    return 0;
}