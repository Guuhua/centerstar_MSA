#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int findMaxCol(char **strs, int num);

char **alignToALL(char **strs, int num, int maxcol);

int *markGapsCenSeq(char **strs, char *centerSeq, int num);

char **insertGapsToStrs(char **res, char *centerSeq, int *marks, int maxcol, int num);

char *InsertGaps(int *marks, char *Seq, int length);

char **starAlign(char **strs, int num);