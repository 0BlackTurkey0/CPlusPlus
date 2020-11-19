#include "Game.h"

using namespace std;

Game::Game(size_t num){
    int alloc[52] = {0}, cnt = 0, ran;
    while(cnt < 24){
        ran = rand() % (52 - cnt) + 1;
        int i = 0;
        while(ran){
            if(!alloc[i])
                ran--;
            if(!ran)
                alloc[i] = cnt % num + 1;
            i++;
        }
        cnt++;
    }
    vector<Card> tmp[4];
    for(size_t i = 0;i < 52;i++){
        if(alloc[i] > 0)
            tmp[alloc[i]-1].push_back(Card(i));
    }
    for(size_t i = 0;i < num;i++){
        player.push_back(Player(tmp[i]));
    }
    while(cnt < 48){
        ran = rand() % (52 - cnt) + 1;
        int i = 0;
        while(ran){
            if(!alloc[i])
                ran--;
            if(!ran){
                alloc[i] = -1;
                Deck.push_back(Card(i));
            }
            i++;
        }
        cnt++;
    }
    for(size_t i = 0;i < 52;i++){
        if(!alloc[i])
            Field.push_back(Card(i));
    }
}

void Game::sgame(){
    system("CLS");
    size_t starter = rand() % player.size();
    printfield(-1);
    for(size_t i = 0;i < 24;i++){
        size_t turn = (starter+i) % player.size();
        if(turn){
            int Maxh, Maxf;
            bool allow = false;
            for(size_t j = 0;j < Field.size();j++){
                for(size_t k = 0;k < player[turn].GetHand().size();k++){
                    if(check(player[turn].GetHand()[k], Field[j])){
                        if(!allow){
                            Maxh = k;
                            Maxf = j;
                            allow = true;
                        }
                        else if(player[turn].GetHand()[Maxh]+Field[Maxf] < player[turn].GetHand()[k]+Field[j]){
                            Maxh = k;
                            Maxf = j;
                        }
                    }
                }
            }
            Position(0,0);
            cout << "                            ";
            Position(0,0);
            cout << "AI" << turn << "'s turn";
            Sleep(2000);
            if(allow){
                player[turn].GetHand()[Maxh].Show(65,6);
                Position(0,0);
                Sleep(2000);
                player[turn].SetScore(player[turn].GetScore()+(player[turn].GetHand()[Maxh]+Field[Maxf]));
                player[turn].GetCover().push_back(player[turn].GetHand()[Maxh]);
                player[turn].GetCover().push_back(Field[Maxf]);
                Field.erase(Field.begin()+Maxf);
                player[turn].GetHand().erase(player[turn].GetHand().begin()+Maxh);
            }
            else{
                int ran = rand()%player[turn].GetHand().size();
                player[turn].GetHand()[ran].Show(65,7);
                Position(0,0);
                Sleep(2000);
                Field.push_back(player[turn].GetHand()[ran]);
                player[turn].GetHand().erase(player[turn].GetHand().begin()+ran);
            }
            system("CLS");
            printfield(turn);
            Sleep(2000);
            Card tmp = Deck[Deck.size()-1];
            tmp.Show(65,0);
            Deck.pop_back();
            Sleep(2000);
            allow = false;
            for(size_t j = 0;j < Field.size();j++){
                if(check(tmp, Field[j])){
                    if(!allow){
                        Maxf = j;
                        allow = true;
                    }
                    else if(tmp+Field[Maxf] < tmp+Field[j])
                        Maxf = j;
                }
            }
            if(allow){
                player[turn].SetScore(player[turn].GetScore()+(tmp+Field[Maxf]));
                player[turn].GetCover().push_back(tmp);
                player[turn].GetCover().push_back(Field[Maxf]);
                Field.erase(Field.begin()+Maxf);
            }
            else
                Field.push_back(tmp);
            system("CLS");
            printfield(turn);
            Sleep(2000);
        }
        else{
            size_t hand, field = 0;
            bool allow;
            system("CLS");
            printfield(turn);
            player[0].printhand();
            while(!field){
                allow = false;
                cout << "Choose a card in your hand:";
                cin >> hand;
                while(hand < 1 || hand > player[0].GetHand().size() || !cin){
                    cin.clear();
                    cin.sync();
                    cout << "Wrong input, try again" << endl;
                    cout << "Choose a card in your hand:";
                    cin >> hand;
                }
                for(size_t j = 0;j < Field.size();j++){
                    if(check(player[0].GetHand()[hand-1], Field[j])){
                        allow = true;
                        break;
                    }
                }
                if(allow){
                    cout << "Choose a card on the field that you wanna eat(if you want to change card enter<0>):";
                    cin >> field;
                    while(field < 0 || field > Field.size() || !cin){
                        cin.clear();
                        cin.sync();
                        cout << "Wrong input, try again" << endl;
                        cout << "Choose a card on the field that you wanna eat(if you want to change card enter<0>):";
                        cin >> field;
                    }
                    if(field && !check(player[0].GetHand()[hand-1], Field[field-1])){
                        cout << "You can't use this card to eat that one, choose again!" << endl;
                        field = 0;
                    }
                }
                else{
                    cout << "This card can't eat any card on the field(if you want to change card enter<0>, if you want to put this card on the field enter<1>):";
                    cin >> field;
                    while(field < 0 || field > 1 || !cin){
                        cin.clear();
                        cin.sync();
                        cout << "Wrong input, try again" << endl;
                        cout << "This card can't eat any card on the field(if you want to change card enter<0>, if you want to put this card on the field enter<1>):";
                        cin >> field;
                    }
                }
            }
            if(!allow)
                Field.push_back(player[0].GetHand()[hand-1]);
            else{
                player[0].SetScore(player[0].GetScore()+(player[0].GetHand()[hand-1]+Field[field-1]));
                player[0].GetCover().push_back(player[0].GetHand()[hand-1]);
                player[0].GetCover().push_back(Field[field-1]);
                Field.erase(Field.begin()+field-1);
            }
            player[0].GetHand().erase(player[0].GetHand().begin()+hand-1);
            system("CLS");
            printfield(turn);
            Card tmp = Deck[Deck.size()-1];
            tmp.Show(0,35);
            Position(0,50);
            Deck.pop_back();
            allow = false;
            for(size_t j = 0;j < Field.size();j++){
                if(check(tmp, Field[j])){
                    allow = true;
                    break;
                }
            }
            if(allow){
                field = 0;
                while(!field){
                    cout << "Choose a card on the field that you wanna eat:";
                    cin >> field;
                    while(field < 1 || field > Field.size() || !cin){
                        cin.clear();
                        cin.sync();
                        cout << "Wrong input, try again" << endl;
                        cout << "Choose a card on the field that you wanna eat:";
                        cin >> field;
                    }
                    if(!check(tmp, Field[field-1])){
                        cout << "You can't use this card to eat that one, choose again!" << endl;
                        field = 0;
                    }
                }
                player[0].SetScore(player[0].GetScore()+(tmp+Field[field-1]));
                player[0].GetCover().push_back(tmp);
                player[0].GetCover().push_back(Field[field-1]);
                Field.erase(Field.begin()+field-1);
            }
            else{
                cout << "This card can't eat any card on the field!" << endl;
                system("pause");
                Field.push_back(tmp);
            }
            system("CLS");
            printfield(turn);
        }
    }
    system("CLS");
    int top = player[0].GetScore();
    for(size_t i = 1;i < player.size();i++){
        if(player[i].GetScore() > top)
            top = player[i].GetScore();
    }
    cout << "Your Score:" << player[0].GetScore();
    if(top == player[0].GetScore())
        cout << "(Winner)";
    cout << endl << "Your Covered Card:" << endl;
    player[0].printcover(GetPosition().Y);
    for(size_t i = 1;i < player.size();i++){
        cout << "AI" << i << "'s Score:" << player[i].GetScore();
        if(top == player[i].GetScore())
            cout << "(Winner)";
        cout << endl << "AI" << i << "'s Covered Card:" << endl;
        player[i].printcover(GetPosition().Y);
    }
}

void Game::printfield(int turn){
    size_t x = 1, y = 2;
    Position(0,0);
    if(!turn)
        cout << "Your turn";
    else if(turn > 0)
        cout << "AI" << turn << "'s turn";
    for(size_t i = 0;i < Field.size();i++){
        Field[i].Show(x, y);
        Position(x+1);
        cout << "<" << i+1 << ">";
        x+=11;
        if(i%6 == 5){
            x = 1;
            y+=16;
        }
    }
    cout << endl;
}

bool check(Card &hand, Card &field){
    int hpoint = hand.GetID()%13+1;
    int fpoint = field.GetID()%13+1;
    if(hpoint > 0 && hpoint < 10){
        if(hpoint+fpoint == 10)
            return true;
    }
    else{
        if(hpoint == fpoint)
            return true;
    }
    return false;
}
