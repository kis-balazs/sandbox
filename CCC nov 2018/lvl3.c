#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int main()
{
    int n;
    FILE *file = fopen("text.in", "r");
    FILE *fileOut = fopen("out.txt", "w");
    fscanf(file, "%d", &n);

    for(int i = 0; i < n; i++)
    {
        int r1, r2, c1, c2;
        double rd1, rd2, cd1, cd2;
        fscanf(file, "%d %d %d %d", &r1, &c1, &r2, &c2);
        rd1 = r1 + 0.5;
        cd1 = c1 + 0.5;
        rd2 = r2 + 0.5;
        cd2 = c2 + 0.5;

        double Rt = 0.000;
        double vX = (rd2 - rd1);
        double vY = (cd2 - cd1);
        double R = r1, C = c1;
        fprintf(fileOut, "%d %d ", r1, c1);
        for(Rt = 0.000; Rt < 1.000; Rt += 0.001)
        {
            if((int)(vX * Rt + rd1) != R || (int)(vY * Rt + cd1) != C)
            {
                fprintf(fileOut, "%d %d ", (int)(vX * Rt + rd1), (int)(vY * Rt + cd1));
                C = (int)(vY * Rt + cd1);
                R = (int)(vX * Rt + rd1);
            }
        }
        fprintf(fileOut, "\n");
    }
    return 0;
}
