#include "ConcreteCards.h"
#include <iostream>

int main() {
    system("chcp 65001");
    std::string strikeName = "打击";
    std::string defendName = "防御";
    std::string bashName = "痛击";

    // 将具体的卡牌对象作为“原型”注册进图鉴
    CardLibrary::registerCard(strikeName, std::make_unique<StrikeCard>(StrikeCard("打击", 1)));
    CardLibrary::registerCard(defendName, std::make_unique<DefendCard>(DefendCard("防御", 1)));
    CardLibrary::registerCard(bashName, std::make_unique<BashCard>(BashCard("痛击", 2)));

    // ==========================================
    // 阶段 2：创建玩家与卡牌发放
    // ==========================================
    Player ironclad(70,3); // 创建拥有 3 点初始能量的战士角色

    // 重点：此时不再手动 new 具体类，而是让图鉴通过 clone() 帮我们生成！
    // 这样游戏的主逻辑完全不知道 StrikeCard、DefendCard 的存在，实现了极度解耦。
    std::unique_ptr<Card> c1 = CardLibrary::createCard(strikeName);
    std::unique_ptr<Card> c2 = CardLibrary::createCard(defendName);
    std::unique_ptr<Card> c3 = CardLibrary::createCard(bashName);
    std::unique_ptr<Card> c4 = CardLibrary::createCard(strikeName); // 再抽一张打击

    if (c1 && c2 && c3 && c4) {
        ironclad.drawCard(std::move(c1));
        ironclad.drawCard(std::move(c2));
        ironclad.drawCard(std::move(c3));
        ironclad.drawCard(std::move(c4));
    }

    // ==========================================
    // 阶段 3：执行出牌逻辑
    // ==========================================
    std::cout << "--- 玩家开始出牌 ---" << std::endl;
    Monster jawWorm("大颚虫", 40); // 创造一个有40点血的怪物
    ironclad.playAllCards(jawWorm); // 把大颚虫传进去挨打
    return 0;
}