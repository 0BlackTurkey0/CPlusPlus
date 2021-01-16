#include <iostream>
#include <cstdio>
#include <cmath>
#include <windows.h>
#include <time.h>

#define pi acos(-1)

int Score = 0, TimeCnt = 0, SugarCnt = 0, SugarCD = 0;
int Sugar_x[5], Sugar_y[5];
float CosX, SinX, CosY, SinY;
int cx = 40, cy = 12, Rx = 40, Ry = -100;
float Tx = 40, Ty = 100, Tz;
int R = 10,r = 5;
float XAngle = 0, YAngle = 0;
float Depth[2000];
char Donut[2000];
float spd = pi/540;

void HideCursor();
void Position(int, int);
void Color(DWORD);
void DataRefresh();
void ColorPrint(const char*, DWORD);
void DonutCalc();
void ScreenUpdate();
void CharacterControl();
void Trace();
void SugarGen();


int main(){
    srand(time(NULL));
    HideCursor();
    Position(0,0);
    bool Gameover = false;
    while(!Gameover){
        DataRefresh();

        ScreenUpdate();

        if(cx==Rx && cy==Ry)
	    Gameover = true;
        else{
            CharacterControl();

            Trace();

            DonutCalc();

            SugarGen();
        }
        Sleep(10);
    }
    Position(80,1);
    ColorPrint("GameOver!!!",12);
    Sleep(100000);
    return 0;
}

void HideCursor(){
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Position(int x, int y){
    COORD coordinate = {(short)x, (short)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

void Color(DWORD color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void DataRefresh(){
    CosX = cos(XAngle);
    SinX = sin(XAngle);
    CosY = cos(YAngle);
    SinY = sin(YAngle);

    Tz = SinX*CosY;
    if(Tz > 0){
        Tx = SinX*SinY;
        Ty = CosX;
        Tx = 110*Tx/Tz+40;
        Ty = 110*Ty/Tz-12;
        Rx = Tx+0.5;
        Ry = -Ty+0.5;
    }
    if(TimeCnt<1200){
        spd += pi/864000;
        TimeCnt++;
    }
    Position(80,0);
    std::cout << "Score:" << Score;
    Position(92,0);
    //std::cout << "SpeedRate:" << spd/pi*360;
}

void ColorPrint(const char *str, DWORD clr){
    Color(clr);
    fputs(str, stdout);
    Color(0xF);
}

void DonutCalc(){
    memset(Donut,32,2000);
    memset(Depth,0,8000);
    for(float RAngle = 0;RAngle < 2*pi;RAngle += pi/180){
        float CosR = cos(RAngle), SinR = sin(RAngle);
        /*
        float Xc_init = R*CosR, Yc_init = 0, Zc_init = -R*SinR;
        float Xc_r = Xc_init, Yc_r = Yc_init*CosX-Zc_init*SinX, Zc_r = Yc_init*SinX+Zc_init*CosX;
        float Xc_rr = Xc_r*CosY+Zc_r*SinY, Yc_rr = Yc_r, Zc_rr = -Xc_r*SinY+Zc_r*CosY;
        */
        float Y_c = R*SinR*SinX;
        for(float rAngle = 0; rAngle < 2*pi; rAngle += pi/90){
            float Cosr = cos(rAngle), Sinr = sin(rAngle);
            float X_init = (r*Cosr+R)*CosR, Y_init = r*Sinr, Z_init = -(r*Cosr+R)*SinR;
            float X_r = X_init, Y_r = Y_init*CosX-Z_init*SinX, Z_r = Y_init*SinX+Z_init*CosX;
            float X_rr = X_r*CosY+Z_r*SinY, Y_rr = Y_r, Z_rr = -X_r*SinY+Z_r*CosY;
            float X = X_rr*100/(210-Z_rr)+20, Y = Y_rr*100/(210-Z_rr)-12, Z = Z_rr+20;
            int Loc = (int)(X*2+0.5) + (int)(-Y+0.5)*80; //2*width = height(character) and Rounding
            int Light = (int)(7.5*(Y_rr-Y_c)/r+4); //light level -4~11 and Rounding
            if(-Y >= 0 && -Y < 25 && X >= 0 && X < 40 && Z > Depth[Loc]){
                Depth[Loc] = Z;
                Donut[Loc] = ".:;!oxOX%#$@"[Light>0?Light:0];
            }
        }
    }
}

void ScreenUpdate(){
    Position(0,0);
    for(int k = 0; k <= 2000; k++){
        if(k%80 == 0 && k)
            putchar('\n');

        bool allow = true;
        if(k%80 == Rx && k/80 == Ry){
            ColorPrint("T",12);
            allow = false;
        }
        else if(k%80 == cx && k/80 == cy){
            ColorPrint("A",14);
            allow = false;
        }
        else
            for(int i = 0;i < SugarCnt;i++){
                if(k%80 == Sugar_x[i] && k/80 == Sugar_y[i]){
                    ColorPrint("S", 13);
                    allow = false;
                }
            }
        if(allow)
            putchar(Donut[k]); //or use _putchar_nolock() in Windows !B putchar_unlocked() in POSIX
    }

}

void CharacterControl(){
    int hor = 0, ver = 0;
    if(GetAsyncKeyState('W') & 0x8000 && cy > 0)
        ver--;
    if(GetAsyncKeyState('S') & 0x8000 && cy < 23)
        ver++;
    if(GetAsyncKeyState('A') & 0x8000 && cx > 0)
        hor--;
    if(GetAsyncKeyState('D') & 0x8000 && cx < 78)
        hor++;
    cx+=hor;
    cy+=ver;
}

void Trace(){
    float ax = cx-40, ay = -cy+12, bx = Tx-40, by = Ty+12;

    float Ang = acos((ax*bx+ay*by+110*110)/sqrt(ax*ax+ay*ay+110*110)/sqrt(bx*bx+by*by+110*110));
    float AngX = acos((ax*ax+ay*by+110*110)/sqrt(ax*ax+ay*ay+110*110)/sqrt(ax*ax+by*by+110*110));
    float AngY = acos((ax*bx+ay*ay+110*110)/sqrt(ax*ax+ay*ay+110*110)/sqrt(bx*bx+ay*ay+110*110));

    float rate;
    if(Ang < spd)
        rate = 1;
    else
        rate = spd/Ang;
    if(cy-Ry > 0)
        XAngle += AngX*rate;
    else if(cy-Ry < 0)
        XAngle -= AngX*rate;
    if(cx-Rx > 0)
        YAngle += AngY*rate;
    else if(cx-Rx < 0)
        YAngle -= AngY*rate;
}

void SugarGen(){
    for(int i = 0;i < SugarCnt;i++){
        if(cx == Sugar_x[i] && cy == Sugar_y[i]){
            if(i != SugarCnt-1){
                Sugar_x[i] = Sugar_x[SugarCnt-1];
                Sugar_y[i] = Sugar_y[SugarCnt-1];
            }
            SugarCnt--;
            Score++;
        }
    }

    if(SugarCD <= 0){
        bool nopass = false;
        do{
            Sugar_x[SugarCnt] = rand()%79;
            Sugar_y[SugarCnt] = rand()%24;
            for(int i = 0;i < SugarCnt;i++)
                if(Sugar_x[SugarCnt] == Sugar_x[i] && Sugar_y[SugarCnt] == Sugar_y[i])
                    nopass = true;
        }while(nopass);
        SugarCnt++;
        SugarCD = 30;
    }
    else if(SugarCnt < 5)
        SugarCD--;
}
