#include "generator.h"

int val_per_constraints(int nb_val, int durete)
{
    return (nb_val * nb_val) * durete / 100;
}

void afficher_contraintes(int n, Couple ***solution, int m)
{
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            if (solution[i][j] != NULL)
            {
                printf("%d ; %d: ", i, j);
                for (int k = 0 ; k < m ; k++)
                {
                    printf("{%d,%d}/",solution[i][j][k].a,solution[i][j][k].b);
                }
                printf("\n");
            }
        }
    }
}

void free_csp(int n, Couple ***solution)
{
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            if (solution[i][j] != NULL)
            {
                free(solution[i][j]);
            }
        }
        free(solution[i]);
    }
    free(solution);
}

void delete_element(int *tab, int val, int pos)
{
    for (int i = pos; i < val - 1; i++)
    {
        tab[i] = tab[i + 1];
    }
}

int *generate_values_array(int nb, int *out)
{
    for (int i = 0 ; i < nb ; i++)
        out[i] = i;
    return out;
}

Couple *generate_value(int val, int *tab, int size)
{
    Couple *constraint = malloc(val * sizeof(Couple));
    int squared_size = size * size;

    for (int i = 0; i < val; i++) {
        int rand_value = rand() % squared_size;
        int found_value = tab[rand_value];
        constraint[i].a = found_value / size;
        constraint[i].b = found_value % size;
        delete_element(tab, squared_size, rand_value);
        squared_size--;
    }
    return constraint;
}

Couple ***generate_constraints(int nb_var, int nb_val, int densite, int durete, int *contraintes, Couple ***solution)
{
    int *values = malloc(nb_val * nb_val * sizeof(int));
    int max_val = (nb_var * (nb_var - 1) / 2); //Total de contrainte
    int val = max_val * densite / 100; //Quantité de contraintes maximum
    int max_nb_val = val_per_constraints(nb_val, durete); //Quantité de valeur !!!!

    for (int i = 0 ; i < val ; i++)
    {
        int rand_value = rand() % max_val;
        int c;
        c = contraintes[rand_value];
        //Réalise une copie du tableau de valeurs possible pour économiser du temps
        //Enfait c'est plus rapide de "reconstruire le tableau" que de le copier (0.03 sec)
        //Et un peu plus efficace enterme de mémoire allouée
        //memcpy(tmp, values, (sizeof(int) * nb_val * nb_val));
        values = generate_values_array(nb_val * nb_val, values);
        solution[c/nb_var][c%nb_var] = generate_value(max_nb_val, values, nb_val);
        delete_element(contraintes, max_val, rand_value);
        max_val--;
    }
    free(values); //Memory leaks
    free(contraintes); //More like memory leeks
    return solution;
}

Couple ***generate_csp(int nb_var, int nb_val, int densite, int durete)
{
    int contraintes_size = nb_var * (nb_var - 1) / 2;
    int x = 0;
    
    Couple ***solution = malloc(nb_var * sizeof(Couple**));
    int *contrainte_utilisable = malloc(contraintes_size * sizeof(int));

    for (int i = 0 ; i < nb_var ; i++)
    {
        solution[i] = malloc(nb_var * sizeof(Couple*));
        for (int j = 0 ; j < nb_var ; j++)
        {
            if (j > i)
                contrainte_utilisable[x++] = i * nb_var + j;
            solution[i][j] = NULL;
        }
    }
    return generate_constraints(nb_var, nb_val, densite, durete, contrainte_utilisable, solution);
}
