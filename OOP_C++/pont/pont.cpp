#include <iostream>
#include "kurzor.h"
#include "set_color.h"
#include <dos.h>
#include "graphics.h"
#include <Windows.h>

using namespace std;

class Pont
{
    private:
        int x;
        int y;
        string szin;
        string jel;

    public:
        Pont(int x1 = 0, int y1 = 0, string sz = "", string j = "*")
        {
            x = x1;
            y = y1;
            szin = sz;
            jel = j;
        }
        void    beolvas()
        {
            cout<<"X = "; cin>>x;
            cout<<"Y = "; cin>>y;
            cout<<"Szin = "; cin>>szin;
            cout<<"Jel = "; cin>>jel;
        }
        void    kirajzol()
        {
            if(szin == "szurke")
                SetColor(8);
            else if(szin == "kek")
                SetColor(9);
            else if(szin == "zold")
                SetColor(10);
            else if(szin == "turkiz")
                SetColor(11);
            else if(szin == "piros")
                SetColor(12);
            else if(szin == "rozsaszin")
                SetColor(13);
            else if(szin == "sarga")
                SetColor(14);

            gotoXY(x,y,jel);

            SetColor(15);
        }
        void    kitorol()
        {
            gotoXY(x,y," ");
        }
        void    mozog_fel()
        {
            gotoXY(x,y," ");
            if (y -- >= 0)
                y --;
            kirajzol();
        }
        void    mozog_le()
        {
            gotoXY(x,y," ");
            y ++;
            kirajzol();
        }
        void    mozog_bal()
        {
            gotoXY(x,y," ");
            if (x -- >= 0)
                x --;
            kirajzol();
        }
        void    mozog_jobbra()
        {
            gotoXY(x,y," ");
            x ++;
            kirajzol();
        }
        void    modosit_szin()
        {
            int sin = rand();
            szin = sin;
        }
        void    modosit_jel(string s)
        {
            jel = s;
        }
};
int     main()
{
    Pont x;
    string n;
    int s;

    x.beolvas();
    x.kirajzol();
    cout<<endl;
    cout<<"Torlod? ";
    cin>>n;
    if (n == "igen")
        x.kitorol();
    if (n == "nem")
        cout<<"Jo";
    cout<<endl;
    string irany;
    cout<<"Szeretned mozgatni? ";
    cin>>n;
    if (n == "igen")
    {
        while (!GetAsyncKeyState(VK_CONTROL))
        {
            if (GetAsyncKeyState(VK_UP) & 0x8000)
                x.mozog_fel();
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
                x.mozog_le();
            else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
                x.mozog_bal();
            else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
                x.mozog_jobbra();
            Sleep(100);
            if (GetAsyncKeyState('X') & 0x8000)
                x.modosit_szin();
        }

    }
    else if (n == "nem")
        cout<<"jo"<<endl;

    return (0);
}
