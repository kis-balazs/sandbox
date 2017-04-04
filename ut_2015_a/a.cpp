#include <iostream>
#include <fstream>
using namespace std;

fstream in("a.in", ios::in);
fstream out("a.out", ios::out);

struct betu
{
    char hely;
    string k = "";
} b[26];

int     talal(char x)
{
    int i = 1;
    while (b[i].hely != x)
        i++;
    return (i);
}

int     finder(string a, char x)
{
    int i = 0;
    while (i <= a.length())
    {
        if (a[i] == x)
            return (0);
        i++;
    }
    return (1);
}
int     main()
{
    int n,m;
    while (true)
    {
        in>>n>>m;
        if (n == 0 && m == 0) return (0);
        for(int i = 1; i <= n; i++)
        {
            b[i].hely = 97 + i - 1;
        }
        int i = 1;
        char x,y,rel;
        int elso, masodik;
        while (i <= m)
        {
            in>>x>>rel>>y;
            elso = talal(x);
            masodik = talal(y);
            if (finder(b[masodik].k,x) == 1)
                b[masodik].k +=x;
            i++;
        }
        //for(int i = 1; i <= n; i++) cout<<b[i].hely<<" "<<b[i].k<<endl;
        i = 1;
        while (i <= n)
        {
            int l = 0;
            while (l <= b[i].k.length())
            {
                int m = talal(b[i].k[l]);
                b[i].k += b[m].k;
                int p = 0;
                while (p < b[i].k.length())
                {
                    char x = b[i].k[p];
                    int o = p + 1;
                    while (o <= b[i].k.length())
                    {
                        if (x == b[i].k[o])
                            b[i].k.erase(o,1);
                        o++;
                    }
                    p++;
                }
                l++;
            }
            i++;
        }
        int jo;
        betu c;
        do
        {
            jo = 1;
            for(int i = 1; i < n; i++)
            {
                if (b[i].k.length() > b[i + 1].k.length())
                {
                    c = b[i];
                    b[i] = b[i + 1];
                    b[i + 1] = c;
                    jo = 0;
                }
            }
        }
        while (jo == 0);

        for(int i = 1; i <= n; i++) cout<<b[i].hely<<" "/*<<b[i].k<<endl*/;
        cout<<endl;
    }
    return (0);
}
