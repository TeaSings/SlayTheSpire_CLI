#include "Card_Basic.h"
#include "Player.h"

int main() {
    Player ironclad(3); // 创建战士角色

    // 动态创建具体的子类对象 (在堆上，或者外部管理生命周期)
    Card* c1 = new StrikeCard("打击", 1);
    Card* c2 = new DefendCard("防御", 1);
    Card* c3 = new BashCard("痛击", 2);

    // 将基类指针塞入 Player 的手牌中 (Upcasting 向上转型)
    ironclad.drawCard(c1);
    ironclad.drawCard(c2);
    ironclad.drawCard(c3);

    std::cout << "--- 玩家开始出牌 ---" << std::endl;
    // 见证奇迹的时刻：编译器会通过虚函数表 (vtbl) 动态绑定，执行正确的动作
    ironclad.playAllCards(); 

    // 别忘了释放内存
    delete c1;
    delete c2;
    delete c3;

    return 0;
}