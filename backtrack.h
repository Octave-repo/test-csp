#ifndef BACKTRACK_H
#define BACKTRACK_H

#include "headers.h"

/*Affiche la solution à un problème*/
void print_solution(int *solution, int size);

/*Vérifie si une valeur est cohérente vis à vis des contraintes */
int coherence_check(int n, int nb_var, int *solution, int size, Couple ***csp);

/* Résout le CSP en utilisant la méthode de backtracking*/
int *backtrack(int nb_var, int nb_val, int durete, Couple ***csp);
#endif