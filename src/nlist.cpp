#include "nlist.h"

/* From K&R 6.6 */

static struct nlist *hashtab[HASHSIZE];
unsigned int hash(const char *s) {
    unsigned int hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

static struct nlist *lookup(const char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->key) == 0)
            return np; /* found */
    return NULL;       /* not found */
}

char *getConfig(const char *key) {
    if (lookup(key) == NULL) {
        return '\0';
    } else {
        return lookup(key)->value;
    }
}

char *getConfig(const char *key, const char *defaultValue) {
    if (lookup(key) == NULL) {
        return (char*)defaultValue;
    } else {
        return lookup(key)->value;
    }
}

static char *strdup(char *s) /* make a duplicate of s */ {
    char *p;
    p = (char *) malloc(strlen(s)+1); /* +1 for ’\0’ */
    if (p != NULL)
       strcpy(p, s);
    return p;
}

/**
 * There is no undef since we just read the config in one time. The first
 * instance of a given key will be the one used.
 * */
struct nlist *addConfig(char *key, char *value) {
    struct nlist *np;
    unsigned int hashval;
    if ((np = lookup(key)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->key = strdup(key)) == NULL) {
            return NULL;
        }
        hashval = hash(key);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *) np->value);
    }
    if ((np->value = strdup(value)) == NULL)
        return NULL;
    return np;
}
