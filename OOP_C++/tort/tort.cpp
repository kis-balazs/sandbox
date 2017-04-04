#include <iostream>
#include <math.h>
using namespace std;

class Tort
{
    private:
        int szaml;
        int nev;

        int     lnko(int a, int b)
        {
            if (a % b == 0) return b;
            else return lnko(b, a%b);
        }
    public:
        Tort(int sz = 0, int n = 0)
        {
            szaml = sz;
            nev = n;
        }
        void    kiir()
        {
            int x;

            if (lnko(szaml, nev) > 1)
            {
                x = lnko(szaml,nev);
                szaml /= x;
                nev /= x;
            }
            cout<<szaml<<"/"<<nev<<endl;
        }
        Tort beolvas()
        {
            cout<<"szaml : "; cin>>szaml;
            cout<<"nev : "; cin>>nev;
        }
        void    osszead(Tort t1, Tort t2)
        {
            szaml = t1.szaml * t2.nev + t2.szaml * t1.nev;
            nev = t1.nev * t2.nev;
        }
        void    kivon(Tort t1, Tort t2)
        {
            szaml = t1.szaml * t2.nev - t2.szaml * t1.nev;
            nev = t1.nev * t2.nev;
        }
        void    szoroz(Tort t1, Tort t2)
        {
            szaml = t1.szaml * t2.szaml;
            nev = t1.nev * t2.nev;
        }
        void    osztas(Tort t1, Tort t2)
        {
            szaml = t1.szaml * t2.nev;
            nev = t1.nev * t2.szaml;
        }
};

int     main()
{
    Tort t0(4,4);
    Tort t1(1,4);
    Tort t;

    cout<<"Osszeadas : ";
    t.osszead(t0,t1);
    t.kiir();
    cout<<"Kivonas : ";
    t.kivon(t0,t1);
    t.kiir();
    cout<<"Szoroz : ";
    t.szoroz(t0,t1);
    t.kiir();
    cout<<"Oszt : ";
    t.osztas(t0,t1);
    t.kiir();
    return (0);
}
