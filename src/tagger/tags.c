#include "tags.h"
unsigned long hash(char *tag)
{
    unsigned long hash = 5381;
    int c;
    
    while ((c = *tag++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    
    return hash;
}