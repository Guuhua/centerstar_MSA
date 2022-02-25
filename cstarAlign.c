#include "cstarAlign.h"
#include "PSA_fmindex.h"


int findMaxCol(char **strs, int num)
{
    int col = 0;
    for (int i = 0; i < num; i++)
    {
        col =  strlen(strs[i]) > strlen(strs[col]) ? i : col;
    }
    return col;
}

char **alignToALL(char **strs, int num, int maxcol)
{
    char **res = (char **)malloc(sizeof(char *) * 2 * (num - 1));
    FM *fmA = FMbulid(strs[maxcol]);

    for (int i = 0; i < num - 1; i++)
    {
        int j = i >= maxcol ? i + 1 : i;
        printf("i = %d, j = %d\t", i, j);
        char **temp = AlignStr(fmA, strs[maxcol], strs[j]);
        res[i<<1] = temp[0];
        res[(i<<1)+1] = temp[1];
    }
    
    freeFM(fmA);
    return res;
}

int *markGapsCenSeq(char **strs, char *centerSeq, int num)
{
    int *marks = (int *)malloc(sizeof(int) * (strlen(centerSeq) + 1));
    for (int i = 0; i < num; i++)
    {
        printf("i = %d\t", i);
        int k = 0, counter = 0;
        char *ps = strs[i<<1];
        // printf("%d:%d\t", strlen(ps), strlen(centerSeq));
        for (int j = 0; j < strlen(ps); j++)
        {
            
            if (ps[j] == '-')
            {
                counter++;
            }
            else
            {
                marks[k] = MAX(marks[k], counter);
                counter = 0;
                k++;
            }
        }
        printf("K:%d,",k);
        marks[k] = MAX(marks[k], counter);
    }
    for (int i = 0; i < (strlen(centerSeq) + 1); i++)
    {
        printf("%d,. ", marks[i]);
    }
    return marks;
}

char **insertGapsToStrs(char **res, char *centerSeq, int *marks, int maxcol, int num)
{
    char **strsed = (char **)malloc(sizeof(char *) * num);
    strsed[maxcol] = InsertGaps(marks, centerSeq, strlen(centerSeq) + 1);

    for (int i = 0; i < num - 1; i++)
    {
        printf("ii = %d\t", i);
        char *tempA = res[i<<1];
        int *tempmark = (int *)calloc((strlen(tempA) + 1), sizeof(int));
        int pi = 0, pj = 0, total = 0;
        for (int j = 0; j < strlen(tempA); j++)
        {
            if (tempA[j] == '-')
                total++;
            else
            {
                tempmark[pi++] = marks[pj++] - total;
                while (total != 0)
                {
                    pi++, total--;
                }
            }
        }
        tempmark[pi] = marks[pj] - total;
        if (i >= maxcol)
        {
            strsed[i+1] = InsertGaps(tempmark, res[(i<<1)+1], (strlen(tempA) + 1));
        }
        else
        {
            strsed[i] = InsertGaps(tempmark, res[(i<<1)+1], (strlen(tempA) + 1));
        }
        free(tempmark);
    }
    free(marks);
    for (int i = 0; i < num - 1; i++)
    {
        free(res[i<<1]);
        free(res[(i<<1)+1]);
    }
    free(res);
    return strsed;
}

char *InsertGaps(int *marks, char *Seq, int length)
{
     int record = 0;
     for (int i = 0; i < length; i++)
     {
         record += marks[i];
         if (i < length - 1)
            record++;
     }
     char *seqed = (char *)malloc(sizeof(char) * (record+1));
     seqed[record] = 0;
     record = 0;
     for (int i = 0; i < length; i++)
     {
        memset(seqed+record, '-', marks[i]);
        record += marks[i];
        if (i < length - 1)
        {
            seqed[record] = Seq[i];
            record++;
        }
     }
     return seqed;
}

char **starAlign(char **strs, int num)
{
    // 1. find the max col
    int maxcol = findMaxCol(strs, num);

    // 2. align to All
    printf("1. align");
    char **res = alignToALL(strs, num, maxcol);

    // 3. mark the gaps in center seq
    printf("2. mark");
    int *marks = markGapsCenSeq(res, strs[maxcol], num - 1);

    for (int i = 0; i < strlen(strs[maxcol]); i++)
    {
        printf("%d,, ", marks[i]);
    }

    // 4. insert the gaps
    printf("3. insert");
    return insertGapsToStrs(res, strs[maxcol], marks, maxcol, num);
}