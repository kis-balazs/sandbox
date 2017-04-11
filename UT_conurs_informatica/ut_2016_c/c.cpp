#include <iostream>
#include <fstream>
using namespace std;

fstream in("c.in", ios::in);

struct elemek
{
    int x, y;
} e[1000];

struct elem
{
    int info;
    elem* bal;
    elem* jobb;
};

elem* gyoker = NULL;

int     vegignezx(int n)
{
    int db = 0;
    for(int i = 1; i <= n; i++)
    {
        int h = e[i].x;
        for(int j = 1; j <= n; j++)
            if (e[j].x == h)
                db++;
    }
    return (db);
}

int     vegignezy(int n)
{
    int db = 0;
    for(int i = 1; i <= n; i++)
    {
        int h = e[i].y;
        for(int j = 1; j <= n; j++)
            if (e[j].y == h)
                db++;
    }
    return (db);
}

void    beszur(int x, elem* &gyoker)
{
    if (gyoker == NULL)
    {
        gyoker = new elem;
        gyoker->info = x;
        gyoker->bal = NULL;
        gyoker->jobb = NULL;
    }
    else if (x < gyoker->info) beszur(x,gyoker->bal);
    else beszur(x,gyoker->jobb);
}

int     kiszamol(elem* gyoker)
{
    if (gyoker == NULL) return (0);
    else return 2 * kiszamol(gyoker->bal) + 3 * kiszamol(gyoker->jobb) + 1;
}

int     main()
{

    int m;
    while (m != 0)
    {
        in>>m;
        if (m != 0)
        {
            for(int i = 1; i <= m; i++)
            {
                in>>e[i].x;
                in>>e[i].y;
            }
            if (vegignezx(m) == m && vegignezy(m) == m)
            {
                elemek c;
                int jo;
                do
                {
                    jo = 1;
                    for(int i = 1; i < m; i++)
                        if (e[i].y > e[i + 1].y)
                        {
                            c = e[i];
                            e[i] = e[i + 1];
                            e[i + 1] = c;
                            jo = 0;
                        }
                }
                while (jo == 0);
                ///
                for(int i = 1; i <= m; i++)
                {
                    beszur(e[i].x, gyoker);
                }
                cout<<kiszamol(gyoker)<<endl;
                gyoker = NULL;
            }
            else
                cout<<0<<endl;
                gyoker = NULL;
            }
    }
    return (0);
}
