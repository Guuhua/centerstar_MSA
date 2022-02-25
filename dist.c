#include "dist.h"


float *getdist(char **strs, int idxc, int num)
{
    float *dmatrix = (float *)malloc(sizeof(float) * num);
    for (int i = 0; i < num; i++)
    {
        dmatrix[i] = compare(strs[idxc], strs[i]);
    }
    return dmatrix;
}

float compare(char *s1, char *s2)
{
    int m = strlen(s1);
    if (m != strlen(s2))
    {
        printf("The length of s1 and s2 dont match!\n");
        printf("s1:%s\n", s1);
        printf("s2:%s\n", s2);
        exit(EXIT_FAILURE);
    }

    int match = 0, gap = 0;
    for (int i = 0; i < m; i++)
    {
        if (s1[i] == s2[i])
        {
            (s1[i] == '-') ? (match++) : (gap++);
        }
    }
    return (float) match / (m - gap);
}