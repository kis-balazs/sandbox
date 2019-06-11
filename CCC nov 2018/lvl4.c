#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define swap(t, x, y) {t tmp = x; x = y; y = tmp;}

typedef struct ds{
    int h;
    int r;
    int c;
} DS;

int n, m;

int found(int arr[], int x, int size)
{
    for(int i = 0; i < size; i++)
        if (arr[i] == x)
            return 1;
    return 0;
}

void    bubble(int arr[], int size)
{
    int c;
    for(int i = 0; i < size - 1; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                c = arr[i];
                arr[i] = arr[j];
                arr[j] = c;
            }
        }
    }
}

void    sortB(DS *x, int k)
{
    for(int i = 0; i < k - 1; i++)
    {
        for(int j = i + 1; j < k; j++)
        {
            if (x[i].r > x[j].r)
                swap(DS, x[i], x[j]);
            if (x[i].r == x[j].r)
            {
                if(x[i].c > x[j].c)
                    swap(DS, x[i], x[j]);
            }
        }
    }
}

int    findHeight(int i, int j, int M[n][m])
{
    int h = 0;
    int x = M[i][j];
    while (M[i][j] == x && i < n)
    {
        h++;
        i++;
    }
    return h;
}

int    findWidth(int i, int j, int M[n][m])
{
    int l = 0;
    int x = M[i][j];
    while (M[i][j] == x && j < m)
    {
        l++;
        j++;
    }
    return l;
}

void    visit(int i, int j, int H, int W, int MA[n][m])
{
    for(int iI = i; iI <= i + H - 1; iI++)
        for(int jJ = j; jJ <= j + W - 1; jJ++)
            MA[iI][jJ] = 1;
}

void    findC(int i, int j, int H, int W, int M[n][m], DS *x)
{
    int iM, jM;
    if (H % 2)
        iM = (H + 1) / 2;
    else
        iM = H / 2;
    if (W % 2)
        jM = (W + 1) / 2;
    else
        jM = W / 2;
    iM += i - 1;
    jM += j - 1;

    x->h = M[i][j];
    x->r = iM;
    x->c = jM;

}

int main()
{
    FILE *in  = fopen("text.in", "r");
    FILE *out = fopen("out.txt", "w");
    fscanf(in, "%d %d", &n, &m);

    int M[n][m];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            fscanf(in, "%d", &M[i][j]);

    int MA[n][m];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            MA[i][j] = 0;
    DS b[n * m / 64];
    int k = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if (M[i][j] != 0 && MA[i][j] == 0)
            {
                int H = findHeight(i, j, M);
                int W = findWidth(i, j, M);
                if (H >= 4 && W >= 4)
                {
                    findC(i, j, H, W, M, &b[k]);
                    k++;
                }
                visit(i, j, H, W, MA);
            }
        }
    }
    sortB(b, k);
    for(int i = 0; i < k; i++)
    {
        //printf("(%d %d), %d\n", b[i].r, b[i].c, b[i].h);
        fprintf(out, "%d %d %d ", i, b[i].r, b[i].c);
    }
    return (0);
}
