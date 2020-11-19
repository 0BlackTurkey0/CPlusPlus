#include "Player.h"

using namespace std;

Player::Player(vector<Card> hand):Score(0), Hand(hand){
}

int Player::GetScore(){
    return Score;
}

void Player::SetScore(int score){
    Score = score;
}

vector<Card>& Player::GetHand(){
    return Hand;
}

void Player::SetHand(vector<Card> hand){
    Hand = hand;
}

vector<Card>& Player::GetCover(){
    return Cover;
}

void Player::SetCover(vector<Card> cover){
    Cover = cover;
}

void Player::printhand(){
    size_t x = 1, y = 35;
    Position(x,y-1);
    cout << "Your Poker Card:";
    for(size_t i = 0;i < Hand.size();i++){
        Hand[i].Show(x, y);
        Position(x+1);
        cout << "<" << i+1 << ">";
        x+=11;
        if(i % 6 == 5){
            x = 1;
            y+=16;
        }
    }
    cout << endl;
}

void Player::printcover(int y){
    int x = 2;
    for(size_t i = 0;i < Cover.size();i++){
        Cover[i].Show(x, y);
        Position(x+1);
        cout << "<" << i+1 << ">";
        x+=20;
        if(i%4 == 3){
            x = 2;
            y+=16;
        }
    }
    cout << endl;
}
