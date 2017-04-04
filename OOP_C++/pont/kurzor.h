#ifndef KURZOR_H_INCLUDED
#define KURZOR_H_INCLUDED

#include <iostream>
#include <windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


void gotoXY(int,int);
void gotoXY(int,int,string);

void gotoXY(int x, int y)
{
CursorPosition.X = x;
CursorPosition.Y = y;
SetConsoleCursorPosition(console,CursorPosition);
}

void gotoXY(int x, int y, string text)
{

CursorPosition.X = x;
CursorPosition.Y = y;
SetConsoleCursorPosition(console,CursorPosition);
cout << text;
}

#endif // KURZOR_H_INCLUDED
