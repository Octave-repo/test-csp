#ifndef BACKJUMPING_H
#define BACKJUMPING_H

#include "headers.h"
int coherence_check_last_issue(int n, int nb_var, int *solution, int size, Couple ***csp, int *block);
int *backjump(int nb_var, int nb_val, int durete, Couple ***csp);
int *timed_backjump(int nb_var, int nb_val, int durete, Couple ***csp);
#endif