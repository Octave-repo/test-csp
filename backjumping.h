#ifndef BACKJUMPING_H
#define BACKJUMPING_H

#include "headers.h"
int **create_parents(int nb_var, Couple ***csp);
int closest_parent(int *parent, int nb_var);
void free_parents(int **parents, int size);
void merge_arrays(int *source, int *destination, int size, int n);
int *backjump(int nb_var, int nb_val, int durete, Couple ***csp);
int *timed_backjump(int nb_var, int nb_val, int durete, Couple ***csp);
#endif