#ifndef SET_COLOR_H_INCLUDED
#define SET_COLOR_H_INCLUDED

#include <windows.h>
#include <stdio.h>
//SetColor(int szam);

void SetColor(int ForgC)
{
     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
#endif // SET_COLOR_H_INCLUDED
