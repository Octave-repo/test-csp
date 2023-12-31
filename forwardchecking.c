#include "forwardchecking.h"
#include "generator.h"
#include "nqueen.h"

//Les domaines de définitions sont représenté sous le forme d'un tableau de domaines de définition
int **create_domains(int nb_var, int nb_val) {
    int **out;
    out = malloc(nb_var * sizeof(int *));
    
    for (int i = 0; i < nb_var; i++) {
        out[i] = malloc(nb_val * sizeof(int));
        for (int j = 0; j < nb_val; j++) {
            out[i][j] = j;
            }
    }
    return out;
}

//Vérifie si un domaine est vide
int is_empty(int *domains, int size)
{
    for (int i = 0 ; i < size ; i++)
    {
        if (domains[i] >= 0){
            return 0;
        }
    }
    return 1;
}

//Retourne une valeur du domaine de définition
int val_from_domain(int *domains, int size)
{
    for (int i = 0 ; i < size ; i++)
    {
        if (domains[i] >= 0)
        {
            int tmp = domains[i];
            domains[i] = -1;
            return tmp;
        }
    }
    return -1;
}

//Vérifie si deux valeurs sont cohérente selon une contrainte
int is_ok(int a, int b, Couple *contrainte, int size)
{
    for (int j = 0; j < size; j++)
    {
        Couple c = contrainte[j];
        if (c.a == a && c.b == b && c.a != NONEVALUE && c.b != NONEVALUE)
        {
            return 1;
        }
    }
    return 0;
}

//Supprime une valeur du domaine de définition
int *remove_value_from_domain(int *domain, int value, int size) {
 
    for (int i = 0; i < size; i++) {
        if (domain[i] == value) {
            domain[i] = -1; // Mettre la valeur à -1 pour la supprimer
        }
    }
    return domain;
}

//Révise le domaine de définition
int **revise(int m, int n, int x, int **definitions, int nb_var, int nb_val, Couple ***csp, int size) {
    //n >= m
    //La contrainte entre n et m
    Couple *contrainte = csp[n][m];
    //Pour simplifier plus tard
    int *definition_m = definitions[m];
    
    //Si on a pas de contrainte, inutile de réviser 
    if (!contrainte)
        return definitions;
        
    for (int i = 0 ; i < nb_val ; i++)
    {
        if (!is_ok(x, definition_m[i], contrainte, size)) {
            int tmp = definition_m[i];
            definition_m = remove_value_from_domain(definition_m, definition_m[i], nb_val);
        }

    }
    return definitions;
}

//Fait une copie des domaines sources vers les domaines destination
void copy_domain(int **source, int **destination, int nb_var, int nb_val) {
    for (int i = 0; i < nb_var; i++) {
        for (int j = 0; j < nb_val; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

int *forwardcheck(int nb_var, int nb_val, int durete, Couple ***csp)
{
    int *out;
    clock_t start_time;
    clock_t end_time;
    double execution_time;

    int size = (durete >= 0) ? val_per_constraints(nb_val, durete) : (nb_var * nb_var);
    //Domaines de définition
    int **definitions = create_domains(nb_var, nb_val);
    //Une copie du domaine de définition (peut être pas nécessaire?)
    int **definitions_copy = create_domains(nb_var, nb_val);
    //Liste des derniers domaines de définitions valides
    int ***last_valid_definitions = malloc(nb_var * sizeof(int**));
    for (int a = 0 ; a < nb_var ; a++){
        last_valid_definitions[a] = create_domains(nb_var, nb_val);
    }
    int *solution = malloc(nb_var * sizeof(int));
    for (int n = 0; n < nb_var; n++)
        solution[n] = -1;

    start_time = clock();
    int i = 0;
    while (i < nb_var && i >= 0) {
        int ok = 0;
        while (!ok && !is_empty(definitions[i], nb_val)) {
            int x = val_from_domain(definitions[i], nb_val);
            definitions[i] = remove_value_from_domain(definitions[i], x, nb_val);
            copy_domain(definitions, last_valid_definitions[i], nb_var, nb_val);
            copy_domain(definitions, definitions_copy, nb_var, nb_val);
            // // Di* <- Di* - {x}
            int empty_domain = 0;
            for (int k = i+1; k < nb_var; k++) {
                definitions = revise(k, i, x,definitions, nb_var, nb_val, csp, size);
                if (is_empty(definitions[k], nb_val)) {
                    empty_domain = 1;
                    break;
                }
            }
            if (!empty_domain) {
                solution[i] = x;
                ok = 1;
            } else
            {
                copy_domain(definitions_copy, definitions, nb_var, nb_val);
            }
        }
        if (!ok) {
            i--;
            /*Si on recule, on récupère le dernier domaine de définition valide au temps i
            La condition permet d'empecher de lire une valeur hors du tableau
            (i < 0 si il n y a pas de solution)*/
            if (i >= 0)
                copy_domain(last_valid_definitions[i], definitions, nb_var, nb_val);
        } else {
            i++;
        }
    }
    end_time = clock();
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Temps d'éxecution: %.6f secondes\n", execution_time);
    if (USEDATAFILE)
    {
        FILE *file = fopen(DATAFILE, "a");
        fprintf(file,"%.6f,", execution_time);
        fclose(file);
    }
    //La gestion de la mémoire n'est pas prise en compte dans le temps de calcul de la fonction
    for (int a = 0 ; a < nb_var ; a++){
        for (int b = 0 ; b < nb_var ; b++){
            free(last_valid_definitions[a][b]);
        }
        free(last_valid_definitions[a]);
        free(definitions[a]);
        free(definitions_copy[a]);
    }
    free(last_valid_definitions);
    free(definitions);
    free(definitions_copy);
    //Si i = -1 alors pas de solution (NULL)
    if (i < 0){
        free(solution);
        return NULL;
    }
    return solution;
}