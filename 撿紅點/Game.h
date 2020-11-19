#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <time.h>
#include "Player.h"

using namespace std;

class Game{
    vector<Player> player;
    vector<Card> Deck;
    vector<Card> Field;
public:
    Game(size_t);
    void sgame();
    void printfield(int);
};

bool check(Card&, Card&);

#endif
