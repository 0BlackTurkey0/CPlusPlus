#include <iostream>
#include <iomanip>
#include <windows.h>
#include <time.h>

using namespace std;

class Card{
    string suit;
    string face;
    bool used;
  public:
    Card(string,string);
    void Setused(bool);
    bool Getused();
    void Show(int,int);
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

void Position(int x, int y){
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

COORD GetPosition(){
    CONSOLE_SCREEN_BUFFER_INFO pos;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pos))
        return pos.dwCursorPosition;
    else{
        COORD def = {0, 0};
        return def;
    }
}

void Color(DWORD color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Card::Card(string suit, string face){
    if(InRange(suit, face)){
        this->suit = suit;
        this->face = face;
        used = false;
    }
    else{
        throw "Incorrect input!\nPlease try again!!";
    }
}

void Card::Setused(bool c){
    used = c;
}

bool Card::Getused(){
    return used;
}

void Card::Show(int x, int y){
    Position(x, y++); Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    Position(x, y++); (suit == "Club" || suit == "Spade")?Color(0xF0):Color(0xFC); cout << "  " << left << setw(2) << face << "               "; Color(0x00); cout << "*" << endl;
    Position(x, y++); Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    Position(x, y++); Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;

    if(suit == "Club"){
        Position(x, y++); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xF0); cout << "       *****       "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xF0); cout << "    ***********    "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xF0); cout << "   *************   "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xF0); cout << "    ***  *  ***    "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
    }
    else if(suit == "Diamond"){
        Position(x, y++); Color(0xFC); cout << "         *         "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xFC); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xFC); cout << "      *******      "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xFC); cout << "    ***********    "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xFC); cout << "      *******      "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xFC); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xFC); cout << "         *         "; Color(0x00); cout << "*" << endl;
    }
    else if(suit == "Heart"){
        Position(x, y++); Color(0xFC); cout << "     ***   ***     "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xFC); cout << "    ***** *****    "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xFC); cout << "    ***********    "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xFC); cout << "     *********     "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xFC); cout << "       *****       "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xFC); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xFC); cout << "         *         "; Color(0x00); cout << "*" << endl;
    }
    else{
        Position(x, y++); Color(0xF0); cout << "         *         "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xF0); cout << "      *******      "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xF0); cout << "    ***********    "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xF0); cout << "   *************   "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xF0); cout << "    ***  *  ***    "; Color(0x00); cout << "*" << endl;
        Position(x, y++); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
    }

    Position(x, y++); Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    Position(x, y++); Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    Position(x, y++); (suit == "Club" || suit == "Spade")?Color(0xF0):Color(0xFC); cout << "               " << right << setw(2) << face << "  "; Color(0x00); cout << "*" << endl;
    Position(x, y++); Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    Color(0X0F);
}

int main(){
    srand(time(NULL));
    while(true){
        int remain = 52;
        Card *Deck[52];
        for(int i = 0;i < 4;i++)
            for(int j = 0;j < 13;j++)
                Deck[i*13+j] = new Card(Suit[i],Face[j]);
        bool re = false;
        while(!re){
            int num;
            cout << "�п�J�n��������J�P�ӼơA�|��" << remain << "�i���J�P(��J0�i�����s���@�Ƽ��J�P):";
            cin >> num;
            while(num > remain || num < 0 || !cin){
                cin.clear();
                cin.sync();
                cout << "���~����J!" << endl << "�п�J�n��������J�P�ӼơA�|��" << remain << "�i���J�P(��J0�i�����s���@�Ƽ��J�P):";
                cin >> num;
            }
            if(!num){
                re = true;
                cout << "�w�ͦ��@�Ʒs�����J�P!" << endl;
            }
            else{
                int pos = GetPosition().Y;
                for(int i = 0;i < num;i++){
                    int r = rand() % remain + 1, cnt = -1, j = 0;
                    while(j != r){
                        cnt++;
                        if(!Deck[cnt]->Getused())
                            j++;
                    }
                    Deck[cnt]->Setused(true);
                    Deck[cnt]->Show(i%4*20+1, pos+i/4*16+1);
                    remain--;
                }
            }
        }
    }
    return 0;
}
