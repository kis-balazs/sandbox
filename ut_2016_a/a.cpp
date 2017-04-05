#include <iostream>
#include <vector>
using namespace std;

void    insert(int x, int pos, vector<int> &vec)
{
    vec.insert(vec.begin() + pos, x);
}

int     search(int x, vector<int> &vec)
{
    for(int i = 0;i < vec.size();i++)
    {
        if (vec[i] == x)
          return (1);
    }
    return (0);
}

int     strlen(int x)
{
      int nv = 0;
      while (x != 0)
      {
        nv++;
        x /= 10;
      }
      return (nv);
}

int     comp(int x, int y)
{
      while (strlen(x) != strlen(y))
      {
        if (strlen(x) < strlen(y))
            x = x *
      }
        if (x < y)
          return (x);
        else if (y > x)
          return (y);
      
}
int   main()
{
  vector<int> vec;
  
  vec.push_back(1);
  vec.push_back(2);
  insert(10,0,vec);
  for(int i = 0; i < vec.size(); i++)
    cout << vec[i] << ' ';
  cout<<endl;
  cout<<search(10,vec);
  cout<<endl;
  return (0);
}