#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <map>
#include <memory>

class Monster;
class Player;

class Card {
private:
    std::string _name;
    int _cost;

protected:
    Card (const Card& other);

public:
    Card (const std::string& name = "", const int cost = 0);
    virtual ~Card();

    inline int getCost() const { return _cost; }
    virtual void play (Player& player, Monster& monster) = 0;
    virtual std::unique_ptr<Card> clone () const = 0;
};

class CardLibrary {
private:
    static std::map<std::string, std::unique_ptr<Card>> cardLibrary;
public:
    static void registerCard (const std::string& cardName, std::unique_ptr<Card> cardClassPointer);
    static std::unique_ptr<Card> createCard (const std::string& cardName);
};

#endif