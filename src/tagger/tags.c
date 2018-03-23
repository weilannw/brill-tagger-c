#include "tags.h"
int hash(char *tag)
{
    int hash = 5381;
    int c;
    while ((c = *tag++))
        hash = ((hash << 6) + hash) + c; /* hash * 33 + c */
    return hash;
}