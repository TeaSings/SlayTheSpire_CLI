#include "ConcreteCards.h"
#include "Player.h"
#include "Monster.h"

int main() {
    system("chcp 65001");
    
    // 1. 注册卡牌原型（只注册一次，后续都通过图鉴 clone）
    CardLibrary::registerCard("打击", std::make_unique<StrikeCard>(StrikeCard("打击", 1)));
    CardLibrary::registerCard("防御", std::make_unique<DefendCard>(DefendCard("防御", 1)));
    CardLibrary::registerCard("痛击", std::make_unique<BashCard>(BashCard("痛击", 2)));

    // 2. 创建玩家和怪物
    Player ironclad(70, 3, 0); 
    Monster jawWorm("大颚虫", 40);

    // 3. 初始化卡组 (会自动生成 5打击 4防御 1痛击 并进行首次洗牌)
    std::cout << "========== 游戏初始化 ==========" << std::endl;
    ironclad.initDeck();

    // 4. 模拟游戏主循环 (我们测试模拟 3 个回合)
    std::cout << "\n========== 战斗开始 ==========" << std::endl;

    for (int turn = 1; turn <= 3; ++turn) {
        std::cout << "\n>>> --- 第 " << turn << " 回合开始 --- <<<" << std::endl;
        
        // 阶段一：回合开始，玩家抽 5 张牌
        ironclad.drawCard(5);
        
        // 阶段二：玩家自动出牌
        std::cout << "\n[玩家行动阶段]" << std::endl;
        ironclad.playAllCards(jawWorm);
        
        // 阶段三：怪物行动
        if (jawWorm.isAlive()) {
            std::cout << "\n[怪物行动阶段]" << std::endl;
            std::cout << "大颚虫发起了攻击，造成 6 点伤害！" << std::endl;
            ironclad.takeDamage(6);
        } else {
            std::cout << "\n怪物已死亡，战斗胜利！" << std::endl;
            break;
        }

        // 阶段四：玩家回合结束，未打出的牌进入弃牌堆，清空护盾
        ironclad.endTurn();
    }

    std::cout << "\n========== 战斗结束 ==========" << std::endl;
    
    return 0;
}