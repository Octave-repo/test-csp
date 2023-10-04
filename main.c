#include "generator.h"
#include "backjumping.h"
#include "backtrack.h"

int main (int argc, char **argv)
{
    srand(time(NULL));
    int quantite;
    int nb_var; //Nombre de variable
    int nb_val; // Nombre de valeurs
    int densite; //Densité
    int durete; //Dureté
    Couple ***csp;
    int *solution;

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
    //solution = backtrack(nb_var, nb_val, durete, csp);
    //afficher_contraintes(nb_var, csp, max_nb_val);
    /*solution = backjump(nb_var, nb_val, durete, csp);
    print_solution(solution, nb_var);
    if (solution != NULL)
        free(solution);
    free_csp(nb_var, csp); */  

    for (int i = 0 ; i < quantite ; i ++)
    {
        csp = generate_csp(nb_var, nb_val, densite, durete);
        
        printf("Backjumping: \n");
        solution = timed_backjump(nb_var, nb_val, durete, csp);
        print_solution(solution, nb_var);
        if (solution != NULL)
            free(solution);
        printf("\nBacktrack: \n");
        solution = backtrack(nb_var, nb_val, durete, csp);
        print_solution(solution, nb_var);
        if (solution != NULL)
            free(solution);
        free_csp(nb_var, csp);
        printf("----------------------\n");
    }
        
    
    /*print_solution(solution, nb_var);
    if (solution != NULL)
        free(solution);
    free_csp(nb_var, csp); */
    /* END BLOCK*/
    return 0;
}