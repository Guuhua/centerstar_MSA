#include "fasta.h"
#include "cstarAlign.h"

void main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("\nerror!\n");
        printf("\n  Usage: %s [input filename in fasta format] [output filename]", argv[0]);
        printf("\nExample: %s ./test/rna.fasta ./test/rna.align\n\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *path1 = argv[1];
    char *wpath = argv[2];

    FILE *fp = fopen(wpath, "w");
    if (fp == NULL)
    {
        printf("\nCouldn't open file %s!\n", wpath);
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    char **strs = NULL, **labels = NULL;
    size_t num = 0;

    readFasta(path1, &strs, &labels, &num);

    char **strsed = starAlign(strs, num);

    writeFasta(wpath, strsed, labels, num);

    printf("DONE!\n");

    for (int i = 0; i < num; i++)
    {
        free(labels[i]);
        free(strsed[i]);
        free(strs[i]);
    }
    free(strs);
    free(strsed);
    free(labels);
}