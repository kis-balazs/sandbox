#include <iostream>
#include <vector>
using namespace std;

void    insert(int x, int pos, vector<int> &vec)
{
    vec.insert(vec.begin() + pos, x);
}

int     van_e_pos(int x, vector<int> &vec)
{
    for(int i = 0;i < vec.size();i++)
    {
        if (vec[i] == x)
          return (i);
    }
    return (0);
}

void    feldolgoz(int x, string &x1)
{
    while (x != 0)
    {
        x1 = (char)(x % 10 + '0') + x1;
        x /= 10;
    }
}

int     comp(int x, int y)
{
    string x1 = "",x2 = "";
    feldolgoz(x,x1);
    feldolgoz(y,x2);
    if (x2 > x1) return (1);
      else if (x2 < x1) return (-1);
}
int   main()
{
  vector<int> vec;

  int n,k,m;
  cin>>k>>m;
  int loc = 0;
  vec.push_back(++loc);
  while (van_e_pos(k,vec) != m - 1)
  {
    int i = 0;
    while (comp(vec[i],loc) != -1 && i < vec.size())
      i++;
    insert(loc,i,vec);
    loc++;
  }
  for(int i = 0;i < vec.size();i++)
    cout<<vec[i]<<" ";
  cout<<endl;
  cout<<vec.size();
  return (0);
}
