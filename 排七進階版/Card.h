#ifndef CARD_H
#define CARD_H

using namespace std;

class Card{
    string suit;
    string face;
    int id;
  public:
    Card(string,string);
    string GetSuit();
    string GetFace();
    int GetID();
    void Show(int,int);
};

COORD GetPosition();

void Position(int, int = GetPosition().Y);

void Color(DWORD);

int IDtrans(string,string);

void alloc(short);

void printown();

void printfield();

bool SaveData(int);

bool LoadData();

void sgame();

#endif // CARD_H
