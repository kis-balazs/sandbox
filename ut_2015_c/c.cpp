#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

fstream in("c.in", ios::in);
fstream out("c.out", ios::out);

int     lnko(int a, int b)
{
    if (a % b == 0) return b;
    else return lnko(b, a % b);
}

int     van_e(vector<int> vec, int a)
{
    for(int i = 0; i < vec.size(); i++)
        if (vec[i] == a) return (0);
    return (1);
}

int     main()
{
    int a;
    //while(true)
    //{
        a = 5000;
        if (a == 1) cout<<"Intregul  1 apare in pozitia  1"<<endl;
        else if (a == 2) cout<<"Intregul  2 apare in pozitia  2"<<endl;
        else
        {
            vector<int> vec;

            for(int i = 1; i <= 2; i++)
                vec.push_back(i);
            int db = 1,x;
            int ssz = 2;
            while (ssz != a)
            {
                x = 0;
                int m = 0;
                while (m != ssz)
                {
                    x++;
                    int l = lnko(ssz,x);
                    if (x != ssz && l > 1 && van_e(vec,x))
                    {
                        vec.push_back(x);
                        ssz = vec.at(++db);
                        m = ssz;
                    }

                }
            }
            cout<<"Intregul "<<a<<" apare in pozitia "<<db + 1<<endl;
        }
    //}
    return (0);
}
