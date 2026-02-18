#ifndef CARD_H
#define CARD_H

#include <iostream>

class Card {
private:
    std::string _name;
    int _cost;
public:
    Card (const std::string name = "", const int cost = 0);
    virtual ~Card();

    inline int getCost() const { return _cost; }
    virtual void play () = 0;
};

#endif