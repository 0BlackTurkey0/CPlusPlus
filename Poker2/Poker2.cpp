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

COORD GetPosition(){
    CONSOLE_SCREEN_BUFFER_INFO bi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
    return bi.dwCursorPosition;
}

void Position(int x, int y = GetPosition().Y){
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
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
    Position(x, y); Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    Position(x); (suit == "Club" || suit == "Spade")?Color(0xF0):Color(0xFC); cout << "  " << left << setw(2) << face << "               "; Color(0x00); cout << "*" << endl;
    Position(x); Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    Position(x); Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;

    if(suit == "Club"){
        Position(x); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xF0); cout << "       *****       "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xF0); cout << "    ***********    "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xF0); cout << "   *************   "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xF0); cout << "    ***  *  ***    "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
    }
    else if(suit == "Diamond"){
        Position(x); Color(0xFC); cout << "         *         "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xFC); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xFC); cout << "      *******      "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xFC); cout << "    ***********    "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xFC); cout << "      *******      "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xFC); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xFC); cout << "         *         "; Color(0x00); cout << "*" << endl;
    }
    else if(suit == "Heart"){
        Position(x); Color(0xFC); cout << "     ***   ***     "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xFC); cout << "    ***** *****    "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xFC); cout << "    ***********    "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xFC); cout << "     *********     "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xFC); cout << "       *****       "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xFC); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xFC); cout << "         *         "; Color(0x00); cout << "*" << endl;
    }
    else{
        Position(x); Color(0xF0); cout << "         *         "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xF0); cout << "      *******      "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xF0); cout << "    ***********    "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xF0); cout << "   *************   "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xF0); cout << "    ***  *  ***    "; Color(0x00); cout << "*" << endl;
        Position(x); Color(0xF0); cout << "        ***        "; Color(0x00); cout << "*" << endl;
    }

    Position(x); Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    Position(x); Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
    Position(x); (suit == "Club" || suit == "Spade")?Color(0xF0):Color(0xFC); cout << "               " << right << setw(2) << face << "  "; Color(0x00); cout << "*" << endl;
    Position(x); Color(0xFF); cout << "                   "; Color(0x00); cout << "*" << endl;
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
            cout << "請輸入要抽取的撲克牌個數，尚有" << remain << "張撲克牌(輸入0可提取新的一副撲克牌):";
            cin >> num;
            while(num > remain || num < 0 || !cin){
                cin.clear();
                cin.sync();
                cout << "錯誤的輸入!" << endl << "請輸入要抽取的撲克牌個數，尚有" << remain << "張撲克牌(輸入0可提取新的一副撲克牌):";
                cin >> num;
            }
            if(!num){
                re = true;
                for(int i = 0;i < 52;i++)
                    delete Deck[i];
                cout << "已生成一副新的撲克牌!" << endl;
            }
            else{
                cout << endl;
                int Ypos;
                for(int i = 0;i < num;i++){
                    int r = rand() % remain + 1, cnt = -1, j = 0;
                    while(j != r){
                        cnt++;
                        if(!Deck[cnt]->Getused())
                            j++;
                    }
                    if(!i)
                        Ypos = GetPosition().Y;
                    else if(i%4)
                        Ypos = GetPosition().Y - 15;
                    else{
                        cout << endl;
                        Ypos = GetPosition().Y;
                    }
                    Deck[cnt]->Show(i%4*20+1, Ypos);
                    Deck[cnt]->Setused(true);
                    remain--;
                }
                cout << endl;
            }
        }
    }
    return 0;
}
