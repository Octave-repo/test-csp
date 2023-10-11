#include "generator.h"
#include "backjumping.h"
#include "backtrack.h"

//Les joies des langages sans GC
void free_parents(int **parents, int size)
{
    for(int i = 0 ; i < size ; i++)
    {
        free(parents[i]);
    }
    free(parents);
}

int **create_parents(int nb_var, Couple ***csp)
{
    int **out = malloc(nb_var * sizeof(int*));

    for (int i = 0 ; i < nb_var ; i++)
    {
        out[i] = malloc(nb_var * sizeof(int));
        int x = 0;
        for (int j = 0 ; j < i ; j++)
        {
            if (csp[j][i] != NULL)
                out[i][x] = j;
            else
                out[i][x] = -1;
            x++;
        }
        for (int j = i ; j < nb_var ; j++)
        {
            out[i][x] = -1;
            x++;
        }
    }
    return out;
}

int closest_parent(int *parent, int nb_var)
{
    int out = -1;
    for (int i = 0 ; i < nb_var ; i++)
    {
        if (parent[i] > out)
            out = i;
    }
    return out;
}

void merge_arrays(int *source, int *destination, int size, int n)
{
    for (int i = 0; i < size; i++)
    {
        if (source[i] != -1 && source[i] != n)
        {
            int duplicate = 0;

            for (int j = 0; j < size; j++)
            {
                if (destination[j] == source[i])
                {
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate)
            {
                for (int j = 0; j < size; j++) {
                    if (destination[j] == -1) {
                        destination[j] = source[i];
                        break;
                    }
                }
            }
        }
    }
}

//TODO ça crash en cas de 
int *backjump(int nb_var, int nb_val, int durete, Couple ***csp)
{
    int **parents = create_parents(nb_var, csp);
    int size;
    if (durete <= -1)
        size = nb_var * nb_var;
    else
        size = val_per_constraints(nb_val, durete);
    int ok;
    int i = 0;
    int *solution = malloc(nb_var * sizeof(int));
    for (int n = 0; n < nb_var; n++)
        solution[n] = -1;
    
    while (i < nb_var && i >= 0)
    {
        ok = 0;
        while (!ok && solution[i] < nb_val -1 )
        {
            solution[i]++;
            ok = coherence_check(i, nb_var, solution, size, csp);
        }
        if (ok)
        {
            i++;
        }
        else
        {
            int iprev = i;
            i = closest_parent(parents[i], nb_var);
            //IDK
            merge_arrays(parents[i], parents[iprev], nb_var, i);
            solution[iprev] = -1;
         }
    }
    if (i < 0)
    {
        free(solution);
        free_parents(parents, nb_var);
        //LIBERER LES PARENTS
        return NULL;
    }
    //LIBERER LES PARENTS
    free_parents(parents, nb_var);
    return solution;
}

int *timed_backjump(int nb_var, int nb_val, int durete, Couple ***csp)
{
    int *out;
    clock_t start_time;
    clock_t end_time;
    double execution_time;

    start_time = clock();
    out = backjump(nb_var, nb_val, durete, csp);
    end_time = clock();
    
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Temps d'éxecution: %.6f secondes\n", execution_time);
    return out;
}
