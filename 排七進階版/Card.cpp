#include <iostream>
#include <iomanip>
#include <windows.h>
#include <vector>
#include <fstream>
#include "Card.h"
#define KEY 87

using namespace std;

string Suit[4] = {"Club", "Diamond", "Heart", "Spade"};
string Face[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
size_t num;
int s;
vector<Card> Deck[4], Cover[4];
vector<int> cCP[3];
bool exist[4] = {false, false, false, true};
int upper[4] = {8, 8, 8, 8};
int lower[4] = {6, 6, 6, 6};
int Nscore[4] = {0};
int starter;

Card::Card(string suit, string face){
    if(IDtrans(suit, face)!=-14){
        this->suit = suit;
        this->face = face;
        id = IDtrans(suit, face);
    }
    else{
        throw "Incorrect input!\nPlease try again!!";
    }
}

string Card::GetSuit(){
    return suit;
}

string Card::GetFace(){
    return face;
}

int Card::GetID(){
    return id;
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


int IDtrans(string suit, string face){
    int SR = -1, FR = -1;
    for(size_t i = 0;i < 4;i++){
        if(Suit[i] == suit)
            SR = i;
    }
    for(size_t i = 0;i < 13;i++){
        if(Face[i] == face)
            FR = i;
    }
    return 13*SR+FR;
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

void alloc(short num){
    int c[52] = {0}, cnt = 0, d;
    while(cnt < 52){
        d = rand() % (52 - cnt) + 1;
        int i = 0;
        while(d){
            if(!c[i])
                d--;
            if(!d){
                c[i] = cnt % num + 1;
                if(i == 45)
                    starter = cnt % num;
            }
            i++;
        }
        cnt++;
    }
    for(int i = 0;i < 52;i++){
        Card tmp(Suit[i/13],Face[i%13]);
        Deck[c[i]-1].push_back(tmp);
    }
    for(int i = 1;i < num;i++){
        for(size_t j = 0;j < Deck[i].size();j++){
            int counter = (Deck[i][j].GetID()%13+1)*(-num+1), tmp;
            string s = Deck[i][j].GetSuit();
            if(Deck[i][j].GetID()%13+1 <= 7){
                tmp = j - 1;
                for(int k = Deck[i][j].GetID()%13-1;k >= 0;k--){
                    if(tmp >= 0){
                        if(s == Deck[i][tmp].GetSuit() && k == Deck[i][tmp].GetID()%13){
                                counter += (k+1)*(-num+1);
                                tmp--;
                        }
                        else
                            counter += k+1;
                    }
                    else
                        counter += k+1;
                }
            }
            if(Deck[i][j].GetID()%13+1 >= 7){
                tmp = j + 1;
                for(int k = Deck[i][j].GetID()%13+1;k < 13;k++){
                    if((size_t)tmp < Deck[i].size()){
                        if(s == Deck[i][tmp].GetSuit() && k == Deck[i][tmp].GetID()%13){
                            counter += (k+1)*(-num+1);
                            tmp++;
                        }
                        else
                            counter += k+1;
                    }
                    else
                        counter += k+1;
                }
            }
            cCP[i-1].push_back(counter);
        }
    }
}

void printown(){
    int x = 1, y = 45, t = 0;
    Position(x,y-1);
    cout << "Your Poker Card:";
    while(Deck[0][0].GetSuit() != Suit[t])
        t++;
    for(size_t i = 0;i < Deck[0].size();i++){
        if(Deck[0][i].GetSuit() != Suit[t]){
            x = 1;
            y += 17;
            do{
                t++;
            }while(Deck[0][i].GetSuit() != Suit[t]);
        }
        Deck[0][i].Show(x, y);
        Position(x+1);
        cout << "<" << i+1 << ">";
        x += 10;
    }
}

void printfield(int a){
    int x = 2, y;
    for(int i = 0;i < 4;i++){
        if(exist[i]){
            y = 30 - 2*upper[i];
            for(int j = upper[i]-1;j > lower[i];j--){
                Card tmp(Suit[i],Face[j-1]);
                tmp.Show(x, y);
                y += 2;
            }
        }
        x += 20;
    }
    Position(0,0);
    if(a < 4 && a > 0)
        cout << "AI." << a << "'s Turn";
    else if(!a)
        cout << "Your Turn";
    else
        cout << "End";
}

bool SaveData(int x){
    fstream savedata, cryptdata;
    savedata.open("Poker.dat", ios::out);
    cryptdata.open("system.exe", ios::out);
    if(!savedata || !cryptdata)
        return false;
    else{
        savedata << num << " " << starter << " " << x << endl;
        for(size_t i = 0;i < 4;i++)
            savedata << exist[i] << " ";
        savedata << endl;
        for(size_t i = 0;i < 4;i++)
            savedata << upper[i] << " ";
        savedata << endl;
        for(size_t i = 0;i < 4;i++)
            savedata << lower[i] << " ";
        savedata << endl;
        for(size_t i = 0;i < num;i++){
            savedata << Deck[i].size() << "  ";
            for(size_t j = 0;j < Deck[i].size();j++)
                savedata << Deck[i][j].GetID() << " ";
            savedata << endl;
        }
        for(size_t i = 0;i < num;i++){
            savedata << Cover[i].size() << "  ";
            for(size_t j = 0;j < Cover[i].size();j++)
                savedata << Cover[i][j].GetID() << " ";
            savedata << endl;
        }
        for(size_t i = 0;i < num-1;i++){
            for(size_t j = 0;j < Deck[i+1].size();j++)
                savedata << cCP[i][j] << " ";
            savedata << endl;
        }
        for(size_t i = 0;i < num;i++)
            savedata << Nscore[i] << " ";

        cryptdata << (num^KEY) << " " << (starter^KEY) << " " << (x^KEY) << " ";
        for(size_t i = 0;i < 4;i++)
            cryptdata << (exist[i]^KEY) << " ";
        for(size_t i = 0;i < 4;i++)
            cryptdata << (upper[i]^KEY) << " ";
        for(size_t i = 0;i < 4;i++)
            cryptdata << (lower[i]^KEY) << " ";
        for(size_t i = 0;i < num;i++){
            cryptdata << (Deck[i].size()^KEY) << " ";
            for(size_t j = 0;j < Deck[i].size();j++)
                cryptdata << (Deck[i][j].GetID()^KEY) << " ";
        }
        for(size_t i = 0;i < num;i++){
            cryptdata << (Cover[i].size()^KEY) << " ";
            for(size_t j = 0;j < Cover[i].size();j++)
                cryptdata << (Cover[i][j].GetID()^KEY) << " ";
        }
        for(size_t i = 0;i < num-1;i++){
            for(size_t j = 0;j < Deck[i+1].size();j++)
                cryptdata << (cCP[i][j]^KEY) << " ";
        }
        for(size_t i = 0;i < num;i++)
            cryptdata << (Nscore[i]^KEY) << " ";
        savedata.close();
        cryptdata.close();
        return true;
    }
    return false;
}

bool LoadData(){
    fstream loaddata, cryptdata;
    loaddata.open("Poker.dat", ios::in);
    cryptdata.open("system.exe", ios::in);
    if(!loaddata || !cryptdata)
        return false;
    else{
        int t, ct;
        loaddata >> t;
        cryptdata >> ct;
        if(loaddata.eof() && cryptdata.eof())
            return false;
        while(loaddata && cryptdata){
            if(t != (ct^KEY)){
                cout << "Someone modified the data, it's not cool :(" << endl;
                system("pause");
                return false;
            }
            loaddata >> t;
            cryptdata >> ct;
        }
        if(loaddata || cryptdata){
            cout << "Someone deleted the data, it's not cool :(" << endl;
            system("pause");
            return false;
        }
        loaddata.clear();
        loaddata.sync();
        loaddata.seekg(0, ios::beg);
        loaddata >> num >> starter >> s;
        for(size_t i = 0;i < 4;i++)
            loaddata >> exist[i];
        for(size_t i = 0;i < 4;i++)
            loaddata >> upper[i];
        for(size_t i = 0;i < 4;i++)
            loaddata >> lower[i];
        for(size_t i = 0;i < num;i++){
            size_t siz;
            loaddata >> siz;
            for(size_t j = 0;j < siz;j++){
                int tmp;
                loaddata >> tmp;
                Card ct(Suit[tmp/13], Face[tmp%13]);
                Deck[i].push_back(ct);
            }
        }
        for(size_t i = 0;i < num;i++){
            size_t siz;
            loaddata >> siz;
            for(size_t j = 0;j < siz;j++){
                int tmp;
                loaddata >> tmp;
                Card ct(Suit[tmp/13], Face[tmp%13]);
                Cover[i].push_back(ct);
            }
        }
        for(size_t i = 0;i < num-1;i++){
            for(size_t j = 0;j < Deck[i+1].size();j++){
                int tmp;
                loaddata >> tmp;
                cCP[i].push_back(tmp);
            }
        }
        for(size_t i = 0;i < num;i++)
            loaddata >> Nscore[i];
        loaddata.close();
        cryptdata.close();
        return true;
    }
    return false;
}

void sgame(){
    while(true){
        bool ne = false;
        if(!LoadData())
            ne = true;
        else{
            char a;
            cout << "You have a game record. Do you want to continue?<Y/N>";
            cin >> a;
            while((a != 'Y' && a != 'N') || !cin){
                cout << "Incorrectly Reply\n Do you want to continue?<Y/N>:";
                cin.clear();
                cin.sync();
                cin >> a;
            }
            if(a == 'N')
                ne = true;
            else
                printfield(0);
        }
        if(ne){
            cout << "Enter the player number(With AI)<2><4>:";
            do{
                cin >> num;
                if((num != 2 && num != 4) || !cin){
                    cin.clear();
                    cin.sync();
                    cout << "Incorrect Input! Please enter the player number again(With AI)<2><4>:";
                }
            }while(num != 2 && num != 4);
            for(int i = 0;i < 4;i++){
                Deck[i].clear();
                Cover[i].clear();
                cCP[i].clear();
                upper[i] = 8;
                lower[i] = 6;
                Nscore[i] = 0;
                if(i != 3)
                    exist[i] = false;
            }
            s = 1;
            system("CLS");
            alloc(num);
            for(size_t i = 0;i < Deck[starter].size();i++){
                if(Deck[starter][i].GetID() == 45){
                    Deck[starter].erase(Deck[starter].begin()+i);
                    if(starter)
                        cCP[starter-1].erase(cCP[starter-1].begin()+i);
                    break;
                }
            }
            if(starter)
                cout << "AI." << starter << " starts with Spade 7!";
            else
                cout << "You start with Spade 7!";
            Sleep(2000);
            Card tmp(Suit[3],Face[6]);
            tmp.Show(62,14);
            Position(64,15);
            Sleep(2000);
        }
        for(int i = s;i < 52;i++){
            int avb[8], able = 0;
            int turn = (starter+i)%num;
            for(size_t j = 0;j < Deck[turn].size();j++){
                if(!exist[Deck[turn][j].GetID()/13]){
                    if(Deck[turn][j].GetID()%13 == 6)
                        avb[able++] = j;
                }
                else{
                    if(Deck[turn][j].GetID()%13+1 == upper[Deck[turn][j].GetID()/13] || Deck[turn][j].GetID()%13+1 == lower[Deck[turn][j].GetID()/13])
                        avb[able++] = j;
                }
            }
            Position(0,0);
            cout << "                                                                                   ";
            Position(0,0);
            if(turn < 4 && turn > 0)
                cout << "AI." << turn << "'s Turn";
            else if(!turn)
                cout << "Your Turn";
            Sleep(2000);
            if(turn){
                if(able){
                    int tmp = 0;
                    for(int j = 1;j < able;j++){
                        if(cCP[turn-1][avb[j]] + (Deck[turn][avb[j]].GetID()%13+1) * (num-1) < cCP[turn-1][avb[tmp]] + (Deck[turn][avb[tmp]].GetID()%13+1) * (num-1))
                            tmp = j;
                    }
                    if(Deck[turn][avb[tmp]].GetID() % 13 == 6)
                        exist[Deck[turn][avb[tmp]].GetID() / 13] = true;
                    else if(Deck[turn][avb[tmp]].GetID() % 13 > 6)
                        upper[Deck[turn][avb[tmp]].GetID() / 13]++;
                    else
                        lower[Deck[turn][avb[tmp]].GetID() / 13]--;
                    printfield(turn);
                    Position(20*(Deck[turn][avb[tmp]].GetID()/13)+4,-2*(Deck[turn][avb[tmp]].GetID()%13)+42);
                    Position(GetPosition().X,GetPosition().Y-15);
                    Sleep(2000);
                    Deck[turn].erase(Deck[turn].begin() + avb[tmp]);
                    cCP[turn-1].erase(cCP[turn-1].begin() + avb[tmp]);
                }
                else{
                    int tmp = 0;
                    for(size_t j = 1;j < Deck[turn].size();j++){
                        if(cCP[turn-1][j] > cCP[turn-1][tmp])
                            tmp = j;
                    }
                    Cover[turn].push_back(Deck[turn][tmp]);
                    Nscore[turn] += Deck[turn][tmp].GetID() % 13 + 1;
                    Deck[turn].erase(Deck[turn].begin() + tmp);
                    cCP[turn-1].erase(cCP[turn-1].begin() + tmp);
                    Position(0,0);
                    cout << "AI." << turn << " Covered a Poker Card!";
                    Sleep(3000);
                }
            }
            else{
                printown();
                cout << endl;
                int tmp;
                if(able){
                    bool f = false;
                    do{
                        cout << "Choose a poker card! you are able to choose";
                        for(int j = 0;j < able;j++)
                            cout << "<" << avb[j]+1 << ">";
                        cout << "(if you wanna exit and save data, Input<0>)";
                        cout << ":";
                        cin >> tmp;
                        if(tmp == 0){
                            bool r = SaveData(i);
                            if(r){
                                cout << "Successfully save data!";
                                exit(1);
                            }
                            else
                                cerr << "Something wrong to save data.";
                        }
                        for(int j = 0;j < able;j++){
                            if(tmp-1 == avb[j])
                                f = true;
                        }
                        if(!f || !cin){
                            cout << "Wrong value, please try again!\n";
                            cin.clear();
                            cin.sync();
                        }
                    }while(!f);
                    if(Deck[turn][tmp-1].GetID() % 13 == 6)
                        exist[Deck[turn][tmp-1].GetID() / 13] = true;
                    else if(Deck[turn][tmp-1].GetID() % 13 > 6)
                        upper[Deck[turn][tmp-1].GetID() / 13]++;
                    else
                        lower[Deck[turn][tmp-1].GetID() / 13]--;
                    printfield(turn);
                    Position(20*(Deck[turn][tmp-1].GetID()/13)+4,-2*(Deck[turn][tmp-1].GetID()%13)+42);
                    Position(GetPosition().X,GetPosition().Y-15);
                    Sleep(2000);
                    Deck[turn].erase(Deck[turn].begin() + tmp-1);
                }
                else{
                    cout << "No card can connect, choose a card to cover(if you wanna exit and save data, Input<0>):";
                    cin >> tmp;
                    if(tmp == 0){
                        bool r = SaveData(i);
                        if(r){
                            cout << "Successfully save data!";
                            exit(1);
                        }
                        else
                            cerr << "Something wrong to save data.";
                    }
                    while(tmp < 1 || tmp > (int)Deck[turn].size() || !cin){
                        cout << "Wrong value, please try again!\n";
                        cin.clear();
                        cin.sync();
                        cout << "No card can connect, choose a card to cover:";
                        cin >> tmp;
                    }
                    Cover[turn].push_back(Deck[turn][tmp-1]);
                    Nscore[turn] += Deck[turn][tmp-1].GetID() % 13 + 1;
                    Deck[turn].erase(Deck[turn].begin() + tmp-1);
                }
                system("CLS");
                printfield(turn);
            }
        }
        system("CLS");
        printfield(5);
        Sleep(3000);
        system("CLS");
        int mi = Nscore[0];
        size_t mc = Cover[0].size();
        for(size_t n = 1;n < num;n++){
            if(Nscore[n] < mi){
                mi = Nscore[n];
                mc = Cover[n].size();
            }
            else if(Nscore[n] == mi){
                if(Cover[n].size() < mc)
                    mc = Cover[n].size();
            }
        }
        cout << "Thank U for your playing!!! Do you wanna play again?<Y/N>:" << endl;
        cout << "Your cover point:" << Nscore[0];
        if(mi==Nscore[0] && mc == Cover[0].size())
            cout << "(Winner)";
        cout << endl;
        int x = 1, y = GetPosition().Y;
        for(size_t i = 0;i < Cover[0].size();i++){
            if(i%7 == 0 && i){
                y+=16;
                x = 1;
            }
            Cover[0][i].Show(x, y);
            x += 20;
        }
        cout << endl;
        for(size_t i = 1;i < num;i++){
            cout << endl << "AI." << i << "'s cover point:" << Nscore[i];
            if(mi==Nscore[i] && mc == Cover[i].size())
                cout << "(Winner)";
            cout << endl;
            x = 1;
            y = GetPosition().Y;
            for(size_t j = 0;j < Cover[i].size();j++){
                if(j%7 == 0 && j){
                    y+=16;
                    x = 1;
                }
                Cover[i][j].Show(x, y);
                x += 20;
            }
            cout << endl;
        }
        Position(58,0);
        char r;
        cin >> r;
        while((r != 'Y' && r != 'N') || !cin){
            cout << "Incorrectly Reply\n Do you wanna play again?<Y/N>:";
            cin.clear();
            cin.sync();
            cin >> r;
        }
        if(r == 'N')
            break;
    }
    system("CLS");
}
