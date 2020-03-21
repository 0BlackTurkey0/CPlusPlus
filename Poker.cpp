#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

class Card{
    string suit;
    string face;
  public:
    Card(string,string);
    void Show();
};

string Suit[4] = {"Club", "Diamond", "Heart", "Spade"};
string Face[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

bool InRange(string suit, string face){
    bool SR = false, FR = false;
    for(size_t i = 0;i < 4;i++){
        if(Suit[i] == suit)
            SR = true;
    }
    for(size_t i = 0;i < 13;i++){
        if(Face[i] == face)
            FR = true;
    }
    return SR&&FR;
}

void Color(DWORD color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Card::Card(string suit, string face){
    if(InRange(suit, face)){
        this->suit = suit;
        this->face = face;
    }
    else{
        throw "Incorrect input!\nPlease try again!!";
    }
}

void Card::Show(){
    Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    (suit == "Club" || suit == "Spade")?Color(0xF0):Color(0xFC); cout << "  " << left << setw(2) << face << "               "; Color(0x00); cout << "*" << endl;
    Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;

    if(suit == "Club"){
        Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Color(0xF0); cout << "       *****       "; Color(0x00); cout << "*" << endl;
        Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Color(0xF0); cout << "    ***********    "; Color(0x00); cout << "*" << endl;
        Color(0xF0); cout << "   *************   "; Color(0x00); cout << "*" << endl;
        Color(0xF0); cout << "    ***  *  ***    "; Color(0x00); cout << "*" << endl;
        Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
    }
    else if(suit == "Diamond"){
        Color(0xFC); cout << "         *         "; Color(0x00); cout << "*" << endl;
        Color(0xFC); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Color(0xFC); cout << "      *******      "; Color(0x00); cout << "*" << endl;
        Color(0xFC); cout << "    ***********    "; Color(0x00); cout << "*" << endl;
        Color(0xFC); cout << "      *******      "; Color(0x00); cout << "*" << endl;
        Color(0xFC); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Color(0xFC); cout << "         *         "; Color(0x00); cout << "*" << endl;
    }
    else if(suit == "Heart"){
        Color(0xFC); cout << "     ***   ***     "; Color(0x00); cout << "*" << endl;
        Color(0xFC); cout << "    ***** *****    "; Color(0x00); cout << "*" << endl;
        Color(0xFC); cout << "    ***********    "; Color(0x00); cout << "*" << endl;
        Color(0xFC); cout << "     *********     "; Color(0x00); cout << "*" << endl;
        Color(0xFC); cout << "       *****       "; Color(0x00); cout << "*" << endl;
        Color(0xFC); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Color(0xFC); cout << "         *         "; Color(0x00); cout << "*" << endl;
    }
    else{
        Color(0xF0); cout << "         *         "; Color(0x00); cout << "*" << endl;
        Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Color(0xF0); cout << "      *******      "; Color(0x00); cout << "*" << endl;
        Color(0xF0); cout << "    ***********    "; Color(0x00); cout << "*" << endl;
        Color(0xF0); cout << "   *************   "; Color(0x00); cout << "*" << endl;
        Color(0xF0); cout << "    ***  *  ***    "; Color(0x00); cout << "*" << endl;
        Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
    }

    Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    (suit == "Club" || suit == "Spade")?Color(0xF0):Color(0xFC); cout << "               " << right << setw(2) << face << "  "; Color(0x00); cout << "*" << endl;
    Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    Color(0X0F);
}

int main(){
    while(true){
        try{
            string suit, face;
            cout << "Choose a suit(Club, Diamond, Heart, Spade): ";
            cin >> suit;
            cout << "Choose a face(A, 2, 3,..., 9, 10, J, Q, K): ";
            cin >> face;
            Card card(suit,face);
            card.Show();
        }
        catch(char const*Error){
            cout << Error << endl;
        }
    }
    return 0;
}
