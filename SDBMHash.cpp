#include "SDBMHash.h"


unsigned int SDBM_hash(char *str)  
{  
    unsigned int hash = 0;  
    while (*str)  
    {
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;  
    }
    return (hash & 0x7FFFFFFF);  
};