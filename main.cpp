#include <iostream>
#include <vector>
#include <string>

class Card {
private:
    std::string _name;
    int _cost;
public:
    Card (const std::string name = "", const int cost = 0)
    : _name(name), _cost(cost)
    {}
    virtual ~Card() {}

    inline int getCost() const { return _cost; }
    virtual void play () = 0;
};

class StrikeCard :public Card {
public:
    StrikeCard (const std::string& name = "", const int cost = 0)
    : Card(name, cost)
    {}

    virtual void play () override {
        std::cout << "造成 6 点伤害" << std::endl;
    }
};

class DefendCard :public Card {
public:
    DefendCard (const std::string& name = "", const int cost = 0)
    : Card(name, cost)
    {}

    virtual void play () override {
        std::cout << "获得 5 点格挡" << std::endl;
    }
};

class BashCard :public Card {
public:
    BashCard (const std::string& name, const int cost)
    : Card(name, cost)
    {}

    virtual void play() override {
        std::cout << "造成 8 点伤害，并给予 1 层易伤" << std::endl;
    }
};

class Player {
private:
    std::vector<Card*> handCards;
    int _mana;
public:
    Player (const int mana = 0)
    : _mana(mana)
    {}

    void drawCard (Card*& card) {
        handCards.push_back(card);
    }

    void playAllCards () {
        for (size_t i = 0; i < handCards.size(); ) {
            if (handCards[i]->getCost() <= _mana) {
                handCards[i]->play();
                _mana -= handCards[i]->getCost();
                handCards.erase(handCards.begin() + i);
            } else {
                std::cout << "当前能量不足" << std::endl;
                i++;
            }
        }
        std::cout << "所有牌已出完" << std::endl;
    }
};

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