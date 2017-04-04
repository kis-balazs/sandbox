#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

ifstream in("a.in");

struct elem
{
    int info;
    elem* bal;
    elem* jobb;
};

elem* gyoker=NULL;

void beszur(int x,elem* &gyoker)
{
    if (gyoker==NULL)
    {
        gyoker=new elem;
        gyoker->info=x;
        gyoker->bal=NULL;
        gyoker->jobb=NULL;
    }
    else if (x<gyoker->info) beszur(x,gyoker->bal);
    else beszur(x,gyoker->jobb);
}

void preorder(elem* gyoker)
{
    cout<<(char)gyoker->info;
    if (gyoker->bal!=NULL) preorder(gyoker->bal);
    if (gyoker->jobb!=NULL) preorder(gyoker->jobb);
}

int     main()
{
    string sor, teljes;
    bool jo = true;
    while (jo)
    {
        getline(in,sor);
        if (sor == "*")
        {
            for(int i = 0; i < teljes.length(); i++)
            {
                beszur(teljes[i],gyoker);
            }
            preorder(gyoker);
            cout<<endl;
            gyoker=NULL;
            teljes = "";
        }
        else if (sor == "$")
        {
            jo = false;
            for(int i = 0; i < teljes.length(); i++)
            {
                beszur(teljes[i],gyoker);
            }
            preorder(gyoker);
            free(gyoker);
            teljes = "";
            cout<<endl;
        }
        else
        {
            teljes = sor + teljes;
        }
    }
    return (0);
}
