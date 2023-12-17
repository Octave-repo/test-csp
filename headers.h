#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define DATAFILE "data.csv"
#define USEDATAFILE 0
 
/*Structure d'un couple de valeur*/
typedef struct _couple {
    int a;
    int b;
} Couple; 

#endif