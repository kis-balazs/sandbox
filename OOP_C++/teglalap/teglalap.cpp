#include <iostream>
#include <fstream>
#include "set_color.h"
using namespace std;

fstream in("f.in",ios::in);

class   Teglalap
{
    private:
        int h;
        int l;
        string szin;
        char jel;
    public:
        Teglalap(int hossz = 0, int szelesseg = 0, string sz = "fekete", char j = '-')
        {
            h = hossz;
            l = szelesseg;
            szin = sz;
            jel = j;
        }
        void    kiir()
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

            for(int i = 1; i <= h;i++)
            {
                for(int j = 1; j <= l;j++)
                {
                        if (i == 1 || j == 1 || i == h || j == l)
                            cout<<jel<<" ";
                        else cout<<"  ";
                }
                cout<<endl;
            }
            SetColor(15);
        }
        void    modosit_l()
        {
            int ujl;
            cin>>ujl;
            l = ujl;
        }
        void    modosit_m()
        {
            int ujm;
            cin>>ujm;
            h = ujm;
        }
        void    modosit_szin()
        {
            string ujm;
            cin>>ujm;
            szin = ujm;
        }
        void    modosit_jel()
        {
            char ujm;
            cin>>ujm;
            jel = ujm;
        }
};
int     main()
{
    Teglalap lap(5,6,"turkiz",'/');

    lap.kiir();
    cout<<endl;
    lap.modosit_l();
    lap.kiir();
    cout<<endl;
    lap.modosit_m();
    lap.kiir();
    cout<<endl;
    lap.modosit_szin();
    lap.kiir();
    cout<<endl;
    lap.modosit_jel();
    lap.kiir();
    return (0);
}
