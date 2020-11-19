#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <vector>
#include "Card.h"

using namespace std;

class Player{
    int Score;
    vector<Card> Hand;
    vector<Card> Cover;
public:
    Player(vector<Card>);
    int GetScore();
    void SetScore(int);
    vector<Card>& GetHand();
    void SetHand(vector<Card>);
    vector<Card>& GetCover();
    void SetCover(vector<Card>);
    void printhand();
    void printcover(int);
};

#endif
