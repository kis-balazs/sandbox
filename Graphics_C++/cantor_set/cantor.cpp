#include<graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <cmath>
using namespace std;
const int y = 240;

void    cantor(int x1, int x2, int y, int n)
{
    if (n == 0) line(x1,y,x2,y);
    else
    {
        int x3 = round((x1 + 0.5 * x2) / 1.5);
        int x4 = round((x2 + x3) / 2.0);
        cantor(x1,x3,y,n - 1);
        cantor(x4,x2,y,n - 1);
    }
}

int     main()
{
    int graphdriver,graphmode;

    graphdriver = DETECT;
    initgraph(&graphdriver, &graphmode,"");

    int x1 = 50,x2 = 600,n,y = 10;
    cin>>n;
    for(int i = 1;i <= n;i++)
    {
        cantor(x1,x2,y+=5,i);
    }

    getch();
    return (0);
}
