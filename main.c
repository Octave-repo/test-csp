#include "generator.h"
#include "backjumping.h"
#include "backtrack.h"
#include "nqueen.h"
#include "forwardchecking.h"

// ./csp 1 5 10 50 50

//Execution du programme avec des paramètres (sans le menu)
void menuless(int argc, char **argv)
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

    csp = generate_queen(nb_var);
    printf("Forward checking: \n");
    solution = forwardcheck(nb_var, nb_var, -1, csp);
    print_solution(solution, nb_var);
    if (solution != NULL)
        free(solution);
    printf("-------------------------\n");
    printf("Backjumping:\n");
    solution = timed_backjump(nb_var, nb_var, -1, csp);
    print_solution(solution, nb_var);
    if (solution != NULL)
        free(solution);
    printf("-------------------------\n");
    printf("Backtracking:\n");
    solution = backtrack(nb_var, nb_var, -1, csp);
    print_solution(solution, nb_var);
    if (solution != NULL)
        free(solution);    
    free_csp(nb_var, csp);
    /*
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
        printf("\nForward checking: \n");
        solution = forwardcheck(nb_var, nb_val, durete, csp);
        print_solution(solution, nb_var);
        if (solution != NULL)
            free(solution);
        free_csp(nb_var, csp);
        printf("----------------------\n");
    }
    */
}


void solve(int qte, int nb_var, int nb_val, int durete, Couple ***csp)
{
    int *solution;
    for (int i = 0 ; i < qte ; i++)
    {
        printf("Forward checking: \n");
        solution = forwardcheck(nb_var, nb_val, -1, csp);
        //print_solution(solution, nb_var);
        if (solution != NULL)
            free(solution);
        printf("-------------------------\n");
        printf("Backjumping:\n");
        solution = timed_backjump(nb_var, nb_val, -1, csp);
        //print_solution(solution, nb_var);
        if (solution != NULL)
            free(solution);
        printf("-------------------------\n");
        printf("Backtracking:\n");
        solution = backtrack(nb_var, nb_val, -1, csp);
        //print_solution(solution, nb_var);
        if (solution != NULL)
            free(solution);
        printf("=======================\n");    
    }
}


void menu_queen(){
    int n;
    int qte;

    printf("Nombre de reines (min 1): ");
    scanf("\n%d", &n);
    if (n < 1){
        printf("Valeur incorecte, la valeur 1 sera utilisée.\n");
    }
    printf("Nombre de fois que le problème devra être résolu (min 1): ");
    scanf("\n%d", &qte);
    if (n < 1){
        printf("Valeur incorecte, la valeur 1 sera utilisée.\n");
    }
    printf("\n");
    Couple ***csp;
    csp = generate_queen(n);
    solve(qte, n, n, -1, csp);
    free_csp(n, csp);
}

void menu_random_csp(){

}

void menu()
{
    int choix;
    printf("Choisisez un problème:\n");
    printf("\t-N-reines(1)\n");
    printf("\t-Aléatoire(2)\n");
    printf("\n\t-Quitter(0)\n");
    scanf("%d", &choix);
    switch (choix){
        case 0:
            return;
            break;
        case 1:
            menu_queen();
            break;
        case 2:
            menu_random_csp();
            break;
        default:
            printf("Choix incorrect, sortie du programme;\n");
            break;
    }
}

int main (int argc, char **argv)
{
    //Permet une execution avec argument (plus rapide pour l'évaluation des temps d'éxecution )
    (argc > 1) ? menuless(argc, argv) : menu();
    return 0;
}