#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*Structure d'un couple de valeur*/
typedef struct _couple {
    int a;
    int b;
} Couple; 

/*Retourne la taille du tableau de valeur des contraintes */
int val_per_constraints(int nb_val, int durete);

/*Affiche toutes les contraintes*/
void afficher_contraintes(int n, Couple ***solution, int m);

/*Libère un CSP*/
void free_csp(int n, Couple ***solution);

/*"Supprime" un element de la liste*/
void delete_element(int *tab, int val, int pos);

/*Génère une liste de n valeurs tel que n[x] = x*/
int *generate_values_array(int nb, int *out);

/*Assigne les couples de valeurs associés à une contrainte*/
Couple *generate_value(int val, int *tab, int size);

/*Génère les contraintes du problème*/
Couple ***generate_constraints(int nb_var, int nb_val, int densite, int durete, int *contraintes, Couple ***solution);

/*Génère le CSP (alloue la mémoire + préparation pour les autres fonction)*/
Couple ***generate_csp(int nb_var, int nb_val, int densite, int durete);

#endif