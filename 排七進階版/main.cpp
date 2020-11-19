#include <iostream>
#include <windows.h>
#include <time.h>
#include "Card.h"

using namespace std;

int main(){
    COORD Size = {150, 120}; SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),Size);
    srand(time(NULL));
    sgame();
    return 0;
}
