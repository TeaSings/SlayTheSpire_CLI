#include "Card.h"

std::map<std::string, Card*> CardLibrary::cardLibrary;

Card::Card(const Card& other) 
    : Card(other._name, other._cost) 
    {}

Card::Card(const std::string& name, const int cost)
    : _name(name), _cost(cost)
{}

Card::~Card() {}

void CardLibrary::registerCard (const std::string& cardName, Card* cardClassPointer) {
    if (cardLibrary.find(cardName) == cardLibrary.end()) {
        cardLibrary[cardName] = cardClassPointer;
    } else {
        std::cout << "[Warning]: 当前卡牌已存在于卡牌图鉴中,加入失败。" << std::endl;
    }
}

Card* CardLibrary::createCard (const std::string& cardName) {
    if (cardLibrary.find(cardName) == cardLibrary.end()) {
        std::cout << "[Warning]: 当前卡牌在卡牌图鉴中未找到,克隆失败" << std::endl;
        return nullptr;
    } else {
        return cardLibrary[cardName]->clone();
    }
}

void CardLibrary::clearCardLibrary () {
    for (auto x : cardLibrary) delete x.second;
}