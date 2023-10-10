#include "generator.h"
#include "backjumping.h"

int coherence_check_last_issue(int n, int nb_var, int *solution, int size, Couple ***csp, int *block)
{
    int ok = 1;
    *block = -1;
    for (int i = 0; i < n; i++)
    {
        // Si on a une contrainte entre la variable actuelle (n) et une autre variable (i)
        if (csp[i][n] != NULL)
        {
            int n_value = solution[n];
            int i_value = solution[i];

            int constraint_satisfied = 0;
            for (int j = 0; j < size; j++)
            {
                Couple c = csp[i][n][j];
                if (c.a == n_value && c.b == i_value)
                {
                    constraint_satisfied = 1;
                    break;
                }
            }
            if (!constraint_satisfied)
            {
                *block = i;
                ok = 0; // Constraint not satisfied
                break;
            }
        }
    }
    return ok;
}

int *backjump(int nb_var, int nb_val, int durete, Couple ***csp)
{
    int block = 0;
    int size;
    if (durete <= -1)
        size = nb_var * nb_var;
    else
        val_per_constraints(nb_val, durete);
    int ok;
    int i = 0;
    int *solution = malloc(nb_var * sizeof(int));
    for (int n = 0; n < nb_var; n++)
        solution[n] = -1;

    while (0 <= i && i < nb_var)
    {
        ok = 0;
        while (!ok && solution[i] < nb_val)
        {
            solution[i]++;
            ok = coherence_check_last_issue(i, nb_var, solution, size, csp, &block);
        }
        if ((solution[i] > nb_val || i < 0) && !ok)
        {
            break;
        }
        if (!ok)
        {    
            solution[i] = -1;
            i = block;
        }
        else
        {
            i++;
        }
    }
    if (i < 0)
    {
        free(solution);
        return NULL;
    }
    else
    {
        return solution;
    }
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
