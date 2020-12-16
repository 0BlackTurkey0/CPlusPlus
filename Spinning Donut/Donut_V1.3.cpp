#include <iostream>
#include <cstdio>
#include <cmath>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define pi acos(-1)

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

int main(){
    srand(time(NULL));
    HideCursor();
    int Score = 0, SugarCount = 0, SugarCD = 0;
    int Sugar_x[5], Sugar_y[5];
    int cx = 40, cy = 12;
    int R = 10,r = 5;
    float spd = pi/360;
    float XAngle = 0, YAngle = 0;
    float Depth[2000];
    char Donut[2000];
    Position(0,0);
    bool gameover = false;
    while(!gameover){
        float CosX = cos(XAngle), SinX = sin(XAngle);
        float CosY = cos(YAngle), SinY = sin(YAngle);
        memset(Depth,0,8000);
        memset(Donut,32,2000);
        for(float RAngle = 0;RAngle < 2*pi;RAngle += pi/180){
            float CosR = cos(RAngle), SinR = sin(RAngle);
            float zc = R*SinR;
            float Yc = SinX*zc;
            for(float rAngle = 0; rAngle < 2*pi; rAngle += pi/90){
                float Cosr = cos(rAngle), Sinr = sin(rAngle);
                float x = (r*Cosr+R)*CosR, y = -r*Sinr, z = (r*Cosr+R)*SinR;
                float X = CosY*x+SinX*SinY*y-CosX*SinY*z, Y = CosX*y+SinX*z, Z = SinY*x-SinX*CosY*y+CosX*CosY*z+R+r+3;
                float Xs = X*100/(2*(R+r)+80-Z+100)+20, Ys = Y*100/(2*(R+r)+80-Z+100)+12;
                int Loc = (int)(Xs*2+0.5) + (int)(Ys+0.5)*80; //2*width = height(character) and Rounding
                int Light = (int)(7.5*-(Y-Yc)/r+4); //light level -4~11 and Rounding
                if(25 > Ys && Ys >= 0 && 40 > Xs && Xs >= 0 && Z > Depth[Loc]){
                    Depth[Loc] = Z;
                    Donut[Loc] = ".:;!oxOX%#$@"[Light>0?Light:0];
                }
            }
        }
        Position(0,0);
        for(int k = 0; k <= 2000; k++){
            if(k%80 == 0 && k)
                putchar('\n');
            putchar(Donut[k]); //or use _putchar_nolock() in Windows ¡B putchar_unlocked() in POSIX
        }
        
        Position(cx,cy);
        Color(0xE);
        putchar('A');
        Color(0xF);
        float Tx = 80*SinX*SinY, Ty = 80*CosX, Tz = -SinX*CosY;
        if(Tz != 0){
        	Tx = Tx/Tz+40;
        	Ty = Ty/Tz+12;
		}
		int Rx = Tx+0.5, Ry = Ty+0.5; //rounding
        if(Rx >= 0 && Rx < 79 && Ry >= 0 && Ry < 24 && Tz > 0){
            Position(Rx,Ry);
            Color(0xC);
            putchar('T');
            Color(0xF);
        }
        
        float ax = cx-40, ay = cy-12, bx = Tx-40, by = Ty-12;
        float Ang = acos((ax*bx+ay*by+62*62)/sqrt(ax*ax+ay*ay+62*62)/sqrt(bx*bx+by*by+62*62));
        float AngX = acos((ax*ax+ay*by+62*62)/sqrt(ax*ax+ay*ay+62*62)/sqrt(ax*ax+by*by+62*62));
        float AngY = acos((ax*bx+ay*ay+62*62)/sqrt(ax*ax+ay*ay+62*62)/sqrt(bx*bx+ay*ay+62*62));
        
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
            YAngle -= AngY*rate;
        else if(cx-Rx < 0)
            YAngle += AngY*rate;

        for(int i = 0;i < SugarCount;i++){
            if(cx == Sugar_x[i] && cy == Sugar_y[i]){
                if(i != SugarCount-1){
                    Sugar_x[i] = Sugar_x[SugarCount-1];
                    Sugar_y[i] = Sugar_y[SugarCount-1];
                }
                SugarCount--;
                Score++;
            }
            else{
                Position(Sugar_x[i],Sugar_y[i]);
                Color(0xD);
                putchar('S');
                Color(0xF);
            }
        }

        Position(80,0);
        std::cout << "Score:" << Score;

        if(SugarCD <= 0){
            if(SugarCount < 5){
                bool nopass = false;
                do{
                    Sugar_x[SugarCount] = rand()%79;
                    Sugar_y[SugarCount] = rand()%24;
                    for(int i = 0;i < SugarCount;i++)
                        if(Sugar_x[SugarCount] == Sugar_x[i] && Sugar_y[SugarCount] == Sugar_y[i])
                            nopass = true;
                }while(nopass);
                SugarCount++;
                SugarCD = 30;
            }
        }
        else
            SugarCD--;

		if(cx==Rx && cy==Ry)
			gameover = true;

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
		
        Sleep(10);
    }
    Position(80,1);
    Color(0xC);
    puts("GameOver!!!");
    Color(0xF);
    Sleep(100000);
    return 0;
}
