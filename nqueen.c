#include "nqueen.h"
void display_queen(Couple ***csp, int n)
{
    int size = n *n;
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            if (csp[i][j] != NULL)
            {
                printf("%d ; %d: ", i, j);
                for (int k = 0 ; k < size ; k++)
                {
                    if (csp[i][j][k].a != NONEVALUE)
                        printf("{%d,%d}/",csp[i][j][k].a,csp[i][j][k].b);
                }
                printf("\n");
            }
        }
    }
}

Couple *init_array(int n, Couple *solution)
{
    //Le nombre maximum de contraintes est n^n (en réalité il y'en a moins)
    int size = n * n;
    solution = malloc(size * sizeof(Couple));
    //On remplis de contraintes qui ne pourront jamais être satisfaite (-100 par sécurité)
    for (int i = 0 ; i < size ; i++)
    {
        solution[i].a = NONEVALUE;
        solution[i].b = NONEVALUE;
    }
    return solution;
}

int is_valid_constraint(int i, int j, int ii, int jj)
{
    //Les dames ne peuvent pas être sur la même ligne
    if (ii == jj)
        return 0;
    //Les dames ne peuvent pas être sur la même diagonale
    //Diagonale vers le bas
    if (jj == ii + (j - i))
        return 0;
    //Diagonale vers le haut
    if (jj == ii  - (j - i))
        return 0;
    return 1;
}

//Génère les contraintes pour un couple de reine
Couple *add_constraints(int i, int j, int n, Couple *solution)
{
    int x = 0;
    for (int ii = 0 ; ii < n ; ii++)
    {
        for (int jj = 0 ; jj  < n ; jj++)
        {
            if (is_valid_constraint(i, j, ii, jj))
            {
                solution[x].a = ii;
                solution[x].b = jj;
                x++;
            }
        }
    }
    return solution;
}

Couple ***generate_queen(int n)
{
    Couple ***solution = malloc(n * sizeof(Couple**));
    for (int i = 0 ; i < n ; i++)
    {
        solution[i] = malloc(n * sizeof(Couple*));
        for (int j = 0 ; j < n ; j++)
        {
            if (j > i)
            {
                solution[i][j] = init_array(n, solution[i][j]);
                solution[i][j] = add_constraints(i, j, n, solution[i][j]);
            }
            else
            {
                solution[i][j] = NULL;
            }
        }
    }
    return solution;
}
