#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

extern string Suit[];
extern string Face[];

class Card{
    int ID;
    string suit;
    string face;
public:
    Card(int);
    Card(string, string);
    int GetID();
    string GetSuit();
    string GetFace();
    void Show(int,int);
    int operator+(const Card&);
};

COORD GetPosition();

void Position(int, int = GetPosition().Y);

void Color(DWORD);

#endif
