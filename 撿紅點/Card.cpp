#include "Card.h"

using namespace std;

string Suit[4] = {"Club", "Diamond", "Heart", "Spade"};
string Face[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

Card::Card(int id){
    if(id < 0 || id >= 52)
        throw "ERROR";
    ID = id;
    suit = Suit[id/13];
    face = Face[id%13];
}

Card::Card(string suit, string face){
    int SR = -1, FR = -1;
    for(size_t i = 0;i < 4;i++){
        if(Suit[i] == suit)
            SR = i;
    }
    for(size_t i = 0;i < 13;i++){
        if(Face[i] == face)
            FR = i;
    }
    if(SR == -1 || FR == -1)
        throw "ERROR";
    ID = 13*SR+FR;
    this->suit = suit;
    this->face = face;
}

int Card::GetID(){
    return ID;
}

string Card::GetSuit(){
    return suit;
}

string Card::GetFace(){
    return face;
}

int Card::operator+(const Card &other){
    int total = 0;
    int s = this->ID/13, f = this->ID%13;
    if(s == 1 || s == 2){
        if(f == 0)
            total += 20;
        else if(f < 8)
            total += (f+1);
        else
            total += 10;
    }
    else if(s == 0 && f == 0)
        total+=10;
    s = other.ID/13;
    f = other.ID%13;
    if(s == 1 || s == 2){
        if(f == 0)
            total += 20;
        else if(f < 8)
            total += (f+1);
        else
            total += 10;
    }
    else if(s == 0 && f == 0)
        total+=10;
    return total;
}

void Card::Show(int x, int y){
    Position(x, y); Color(0xFF); cout << "                   "; Color(0x00); cout << "*";
    Position(x, ++y); (suit == "Club" || suit == "Spade")?Color(0xF0):Color(0xFC); cout << "  " << left << setw(2) << face << "               "; Color(0x00); cout << "*";
    Position(x, ++y); Color(0xFF); cout << "                   "; Color(0x00); cout << "*";
    Position(x, ++y); Color(0xFF); cout << "                   "; Color(0x00); cout << "*";

    if(suit == "Club"){
        Position(x, ++y); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xF0); cout << "       *****       "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xF0); cout << "    ***********    "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xF0); cout << "   *************   "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xF0); cout << "    ***  *  ***    "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*";
    }
    else if(suit == "Diamond"){
        Position(x, ++y); Color(0xFC); cout << "         *         "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xFC); cout << "        ***        "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xFC); cout << "      *******      "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xFC); cout << "    ***********    "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xFC); cout << "      *******      "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xFC); cout << "        ***        "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xFC); cout << "         *         "; Color(0x00); cout << "*";
    }
    else if(suit == "Heart"){
        Position(x, ++y); Color(0xFC); cout << "     ***   ***     "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xFC); cout << "    ***** *****    "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xFC); cout << "    ***********    "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xFC); cout << "     *********     "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xFC); cout << "       *****       "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xFC); cout << "        ***        "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xFC); cout << "         *         "; Color(0x00); cout << "*";
    }
    else{
        Position(x, ++y); Color(0xF0); cout << "         *         "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xF0); cout << "      *******      "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xF0); cout << "    ***********    "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xF0); cout << "   *************   "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xF0); cout << "    ***  *  ***    "; Color(0x00); cout << "*";
        Position(x, ++y); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*";
    }

    Position(x, ++y); Color(0xFF); cout << "                   "; Color(0x00); cout << "*";
    Position(x, ++y); Color(0xFF); cout << "                   "; Color(0x00); cout << "*";
    Position(x, ++y); (suit == "Club" || suit == "Spade")?Color(0xF0):Color(0xFC); cout << "               " << right << setw(2) << face << "  "; Color(0x00); cout << "*";
    Position(x, ++y); Color(0xFF); cout << "                   "; Color(0x00); cout << "*";
    Color(0X0F);
}

COORD GetPosition(){
    CONSOLE_SCREEN_BUFFER_INFO bi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
    return bi.dwCursorPosition;
}

void Position(int x, int y){
    COORD coordinate = {(short)x, (short)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

void Color(DWORD color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
