#include "ConcreteCards.h"
#include "Player.h"
#include <iostream>

// 一个辅助函数，用于清理未打出的手牌，防止内存泄漏
void cleanupHand(Player& player) {
    // 实际项目中 Player 应该有自己的析构函数 ~Player() 来处理这个
    // 这里简单演示，如果你没有在 Player 内部处理，就需要在外部手动清理
}

int main() {
    // ==========================================
    // 阶段 1：游戏初始化，注册卡牌原型到图鉴中
    // ==========================================
    // 注意：如果你还没有将 CardLibrary 方法的参数改为 const std::string&，
    // 这里必须借助临时变量，否则会编译报错。建议尽快修改为 const！
    system("chcp 65001");
    std::string strikeName = "打击";
    std::string defendName = "防御";
    std::string bashName = "痛击";

    // 将具体的卡牌对象作为“原型”注册进图鉴
    CardLibrary::registerCard(strikeName, new StrikeCard("打击", 1));
    CardLibrary::registerCard(defendName, new DefendCard("防御", 1));
    CardLibrary::registerCard(bashName, new BashCard("痛击", 2));

    // ==========================================
    // 阶段 2：创建玩家与卡牌发放
    // ==========================================
    Player ironclad(3); // 创建拥有 3 点初始能量的战士角色

    // 重点：此时不再手动 new 具体类，而是让图鉴通过 clone() 帮我们生成！
    // 这样游戏的主逻辑完全不知道 StrikeCard、DefendCard 的存在，实现了极度解耦。
    Card* c1 = CardLibrary::createCard(strikeName);
    Card* c2 = CardLibrary::createCard(defendName);
    Card* c3 = CardLibrary::createCard(bashName);
    Card* c4 = CardLibrary::createCard(strikeName); // 再抽一张打击

    if (c1 && c2 && c3 && c4) {
        ironclad.drawCard(c1);
        ironclad.drawCard(c2);
        ironclad.drawCard(c3);
        ironclad.drawCard(c4);
    }

    // ==========================================
    // 阶段 3：执行出牌逻辑
    // ==========================================
    std::cout << "--- 玩家开始出牌 ---" << std::endl;
    // 应该会出前三张牌 (1+1+2 = 4，但只有3点能量，所以第三张“痛击”出不来，会跳过)
    ironclad.playAllCards(); 
    
    // 如果你修改了 Player.h (加上了 delete)，打出的牌内存会被回收。
    // 但是，因为能量不够没打出的牌（比如痛击和第二张打击）仍然在手牌里，需要有机制回收。

    std::cout << "--- 游戏结束，进行内存清理 ---" << std::endl;
    // 注意：在完整项目中，CardLibrary 内部的原型卡牌（最早 new 出来的那个模板）
    // 也需要一个静态的 clearLibrary() 方法来遍历 map 进行 delete 释放，这里作为进阶思考留给你。

    return 0;
}