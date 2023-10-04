#include "forwardchecking.h"
#include "backtrack.h"


int *forwardcheck(int nb_var, int nb_val, int durete, Couple ***csp)
{
    int *domaine;
    int domain_size = nb_val;
    int n = 0;
    int x;
    int current_val = 0;
    int ok;
    domaine = malloc(nb_val * sizeof(int));
    for (int i = 0 ; i < nb_val ; i++)
        domaine[i] = i;
    
    while (n <= 0 && n <= nb_var)
    {
        ok = 0;
        while (!ok && domain_size > 0)
        {
            
        }
    }
}