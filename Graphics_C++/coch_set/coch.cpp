#include<graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <cmath>

const double PI=3.14159265;

void    forgat(int x0, int y0,int x, int y, double fok, int &xuj, int &yuj)
{
    xuj = round(x0 + (x - x0)*cos(fok) - (y - y0)*sin(fok));
    yuj = round(y0 + (x - x0)*sin(fok) + (y - y0)*cos(fok));
}

void    koch(int x1,int y1, int x2, int y2, int n)
{
    if (n == 0) line(x1,y1,x2,y2);
    else
    {
        int x3 = round((x1 + 0.5 * x2) / 1.5);
        int y3 = round((y1 + 0.5 * y2) / 1.5);
        int x4 = round((x2 + 0.5 * x1) / 1.5);
        int y4 = round((y2 + 0.5 * y1) / 1.5);
        int x5,y5;
        forgat(x3, y3,x4,y4,PI / 3, x5, y5);
        koch(x1,y1,x3,y3,n - 1);
        koch(x3,y3,x5,y5,n - 1);
        koch(x5,y5,x4,y4,n - 1);
        koch(x4,y4,x2,y2,n - 1);
    }
}

void    koch2(int x1,int y1, int x2, int y2, int n)
{
    if (n == 0) line(x1,y1,x2,y2);
    else
    {
        int x3 = round((x1 + 0.5 * x2) / 1.5);
        int y3 = round((y1 + 0.5 * y2) / 1.5);
        int x4 = round((x2 + 0.5 * x1) / 1.5);
        int y4 = round((y2 + 0.5 * y1) / 1.5);
        int x5,y5,x6,y6;
        forgat(x3,y3,x4,y4,PI / 2, x5, y5);
        forgat(x5,y5, x3,y3,PI / 2, x6,y6);
        koch2(x1,y1,x3,y3,n - 1);
        koch2(x3,y3,x5,y5,n - 1);
        koch2(x5,y5,x6,y6,n - 1);
        koch2(x6,y6,x4,y4,n - 1);
        koch2(x4,y4,x2,y2,n - 1);
    }
}

void    sierpinski_3(int x1,int y1, int x2, int y2, int x3, int y3, int n)
{
    if (n == 0){
        line(x1,y1,x2,y2);
        line(x2,y2,x3,y3);
        line(x3,y3,x1,y1);
    }
    else{
    int x4 = round((x1 + x2) / 2.0);
    int x5 = round((x2 + x3) / 2.0);
    int x6 = round((x3 + x1) / 2.0);
    int y4 = round((y1 + y2) / 2.0);
    int y5 = round((y2 + y3) / 2.0);
    int y6 = round((y3 + y1) / 2.0);
    sierpinski_3(x1,y1,x4,y4,x6,y6, n - 1);
    sierpinski_3(x4,y4,x2,y2,x5,y5, n - 1);
    sierpinski_3(x6,y6,x5,y5,x3,y3, n - 1);
    setfillstyle(SOLID_FILL,RED);
    floodfill(round((x1 + x2+ x3) / 3.0), round((y1 + y2 + y3) / 3.0), WHITE);

    }
}

void    sierpinski_4(int x1,int y1, int x2, int y2, int n)
{
    if (n > 0){
        int x3 = round((x1 + 0.5 * x2) / 1.5);
        int x4 = round((x2 + 0.5 * x1) / 1.5);
        int y3 = round((y1 + 0.5 * y2) / 1.5);
        int y4 = round((y2 + 0.5 * y1) / 1.5);
        sierpinski_4(x1,y1,x3,y3, n - 1);
        sierpinski_4(x4,y1,x2,y3, n - 1);
        sierpinski_4(x1,y4,x3,y2, n - 1);
        sierpinski_4(x4,y4,x2,y2, n - 1);
        //rectangle(x1,y1,x2,y2);
        rectangle(x3,y3,x4,y4);
        setfillstyle(SOLID_FILL,RED);
        floodfill(round((x1 + x2) / 2.0), round((y1 + y2) / 2.0), WHITE);
    }
}

int     main()
{
    int graphdriver, graphmode;

    graphdriver = DETECT;
    initgraph(&graphdriver, &graphmode, "");
    int x1 = 100,x2 =500,y1= 10, y2 = 490,n = 4;

    //koch(x1,y1,x2,y2,n);
    //koch2(x2,y2,x1,y1,n);
    //forgat(x1,479,x2,479,-(PI / 3), x3,y3);
    //sierpinski_3(x1,479,x2,479,x3,y3,n);
    sierpinski_4(x1,y1,x2,y2,4);
    getch();
    return (0);
}
