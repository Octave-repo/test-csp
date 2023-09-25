#include "backtrack.h"
#include "generator.h"
void print_solution(int *solution, int size)
{
    if (solution == NULL)
        printf("Aucune solution !\n");
    else
    {
        for (int i = 0 ; i < size ; i++)
        {
            printf("%d ", solution[i]);
        }
        printf("\n");
    }
}

int coherence_check(int n, int nb_var, int *solution, int size, Couple ***csp)
{
    int ok = 1;

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
                ok = 0; // Constraint not satisfied
                break;
            }
        }
    }
    return ok;
}

int backtrack_recursive(int nb_var, int nb_val, int durete, Couple ***csp, int *solution, int current_var)
{
    //Taille du tableau de contrainte
    int size = val_per_constraints(nb_val, durete);

    //Si on a atteint la fin du tableau
    if (current_var >= nb_var)
    {
        return coherence_check(nb_var - 1, nb_var, solution, size, csp);
    }

    //On itère sur le domaine de définition 
    for (int i = 0; i < nb_val; i++)
    {
        //On assigne la valeur
        solution[current_var] = i;
        //Si la valeur est une valeur cohérente   
        if (coherence_check(current_var, nb_var, solution, size, csp))
        {
            //On apelle récursivement la suite
            return backtrack_recursive(nb_var, nb_val, durete, csp, solution, current_var + 1);
        }
    }
    return 0;
}

int *backtrack(int nb_var, int nb_val, int durete, Couple ***csp)
{
    clock_t start_time;
    clock_t end_time;
    double execution_time;
    
    int ok;
    int *solution = malloc(nb_var * sizeof(int));
    for (int n = 0; n < nb_var; n++)
        solution[n] = 0;
    
    start_time = clock();
    ok = backtrack_recursive(nb_var, nb_val, durete, csp, solution, 0);
    end_time = clock();

    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Temps d'éxecution: %.6f secondes\n", execution_time);
    if (ok)
        return solution;
    else
    {
        free(solution);
        return NULL;
    }
}
