#ifndef _NLIST_H
#define _NLIST_H

#include <SPI.h>
#define HASHSIZE 101
struct nlist {
    struct nlist *next;
    char *key;
    char *value;
};

char *getConfig(const char *s);
char *getConfig(const char *key, const char *defaultValue);
struct nlist *addConfig(char *key, char *value);

#endif
