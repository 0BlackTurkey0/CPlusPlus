#include <iostream>
#include <windows.h>
#include <math.h>

#define pi acos(-1)

void HideCursor(){
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Reset(){
    COORD TL = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), TL);
}

int main(){
    HideCursor();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xE);
    int R = 6,r = 3;
    float XAngle = 0, ZAngle = 0;
    float Depth[2000];
    char Donut[2000];
    Reset();
    while(true){
        float CosX = cos(XAngle), SinX = sin(XAngle);
        float CosZ = cos(ZAngle), SinZ = sin(ZAngle);
        memset(Depth,0,7040);
        memset(Donut,32,1760);
        for(float RAngle = 0;RAngle < 2*pi;RAngle += pi/180){
            float CosR = cos(RAngle), SinR = sin(RAngle);
            float Xc = R*CosR, Yc = 0, Zc = R*SinR; //initialize center of r (Non-Rotated)
            float Xcr = Xc, Ycr = SinX*Zc+CosX*Yc; //X-Rotate
            float Ycc = 12+SinZ*(-Xcr)+CosZ*Ycr; //Z-Rotate(Y-Axis)
            for(float rAngle = 0; rAngle < 2*pi; rAngle += pi/90){
                float Cosr = cos(rAngle), Sinr = sin(rAngle);

                float Xi = (r*Cosr+R)*CosR, Yi = r*Sinr, Zi = (r*Cosr+R)*SinR; //initialize Non-Rotated Donut Location
                float Xr = Xi, Yr = SinX*Zi+CosX*Yi, Zr = CosX*Zi-SinX*Yi; //X-Rotate
                float X = 20+CosZ*(-Xr)-SinZ*Yr, Y = 12+SinZ*(-Xr)+CosZ*Yr, Z = 20+Zr; //Z-Rotate(Finish)
                int Loc = (int)(X*2+0.5) + (int)(24-Y+0.5)*80; //2*width = height(character) and Rounding
                int Light = 8*(Y-Ycc)/r+4; //light level -4~12
                float InvZ = 1/Z; //invert Depth for determining front side
                if(25 > Y && Y >= 0 && 40 > X && X >= 0 && InvZ > Depth[Loc]){
                    Depth[Loc] = InvZ;
                    Donut[Loc] = ".:;!oxOX%#$@"[Light>0?Light:0];
                }
            }
        }
        Reset();
        for(int k = 0; k <= 2000; k++)
            std::cout << (k%80?Donut[k]:'\n');
        XAngle += pi/47;
        ZAngle += pi/91;
        Sleep(10);
    }
    return 0;
}

