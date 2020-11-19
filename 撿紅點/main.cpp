#include "Game.h"

using namespace std;

int main()
{
    COORD Size = {150, 350}; SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),Size);
    srand(time(NULL));
    size_t num;
    bool re = true;
    while(re){
        system("CLS");
        cout << "Enter the player number(With AI)<2><3><4>:";
        cin >> num;
        while(num < 2 || num > 4 || !cin){
            cin.clear();
            cin.sync();
            cout << "Wrong input, try again" << endl;
            cout << "Enter the player number(With AI)<2><3><4>:";
            cin >> num;
        }
        Game game(num);
        game.sgame();
        char ans;
        cout << "Do you wanna play again?(Y/N):";
        cin >> ans;
        while((ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') || !cin){
            cin.clear();
            cin.sync();
            cout << "Wrong input, Please try again!" << endl;
            cout << "Do you wanna play again?(Y/N):";
            cin >> ans;
        }
        if(ans == 'Y' || ans == 'y')
            re = true;
        else
            re = false;
    }
    return 0;
}
