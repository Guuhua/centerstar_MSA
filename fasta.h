#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>

#define LEN 60

size_t *countInfo(char *, size_t *);

void readFasta(char *, char ***, char ***, size_t*);

void writeFasta(char *, char **, char **, size_t);
