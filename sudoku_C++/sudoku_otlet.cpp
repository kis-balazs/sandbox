#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

int a[9][9];

bool row(int i, int j, int x)
{
    for(int g=0;g<9;g++)
        if(a[i][g]==x)
            return 0;
    return 1;
}

bool column(int i, int j, int x)
{
    for(int g=0;g<9;g++)
        if(a[g][j]==x)
            return 0;
    return 1;
}

bool square(int i, int j, int x)
{
    int r = ceil((i+1)/3.);
    int c = ceil((j+1)/3.);
    for(int g=(r-1)*3;g<(r-1)*3+3;g++)
        for(int h=(c-1)*3;h<(c-1)*3+3;h++)
        if (a[g][h]==x)
            return 0;
    return 1;
}

int main()
{
    int un = 0,tmp;
    bool b = 1;
    const char* filename = "sudoku.be";
    ifstream in(filename);
    if(!in.is_open())
    {
        cout<<"FILE PROBLEM\n";
        return (0);
    }
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            in>>a[i][j];
            if(!a[i][j])
                un++;
        }
    in.close();
    //main loop
    while (un && b)
    {
        b = 0;
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
            {
                if(a[i][j])
                    continue;
                tmp = 0;
                for(int x=1;x<10;x++)
                {
                    if(row(i,j,x) && column(i,j,x) && square(i,j,x))
                    {
                        if(!tmp)
                            tmp = x;
                        else{
                            tmp = 0;
                            break;
                        }
                    }
                }
                if(tmp)
                {
                    a[i][j] = tmp;
                    b = 1;
                    un--;
                }
            }
    }
    if(!b)
        cout<<"UNSOLVABLE"<<endl;
    else{
        cout<<"SOLVED"<<endl;
    cout<<"\n";
     for(int i=0;i<9;i++)
     {
         for(int j=0;j<9;j++)
            cout<<a[i][j]<<" ";
         cout<<endl;
     }}
    cout<<endl;
    return (0);
}
