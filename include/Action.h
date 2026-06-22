#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <string>

enum class ActionType {
    PlayCard,
    EndTurn
};

struct Action {
    ActionType type;
    int handIndex;
};

struct ActionResult {
    bool ok;
    bool endTurn;
    bool battleEnded;
    std::string messege;
};

#endif