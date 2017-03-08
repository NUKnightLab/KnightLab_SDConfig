#ifndef _NLIST_H
#define _NLIST_H

#include <SPI.h>
#define HASHSIZE 101
struct nlist {
    struct nlist *next;
    char *key;
    char *value;
};

char *getConfig(char *s);
struct nlist *addConfig(char *key, char *value);

#endif
