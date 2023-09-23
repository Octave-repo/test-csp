#include "generator.h"

int main (int argc, char **argv)
{
    srand(time(NULL));
    int quantite;
    int nb_var; //Nombre de variable
    int nb_val; // Nombre de valeurs
    int densite; //Densité
    int durete; //Dureté
    Couple ***solution;

    if (argc < 6)
    {
        printf("Pas suffisament d'arguments.\n");
        exit(0);
    }
    quantite = atoi(argv[1]);
    nb_var = atoi(argv[2]);
    nb_val = atoi(argv[3]);
    densite = atoi(argv[4]);
    //Vérifier si c'est pas l'inverse j'ai un doute
    durete = atoi(argv[5]);

    printf("%d CSP vont être générés avec: \n", quantite);
    printf("- %d variables\n- %d valeurs\n- %d%% de densité\n- %d%% de dureté\n\n"
        ,nb_var, nb_val, densite, durete);

    /* TEST BLOCK*/
    solution = generate_csp(nb_var, nb_val, densite, durete);

    int max_nb_val  = val_per_constraints(nb_val, durete);
    afficher_contraintes(nb_var, solution, max_nb_val);
    free_csp(nb_var, solution);   
    /* END BLOCK*/
    return 0;
}