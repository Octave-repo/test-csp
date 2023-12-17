#include "generator.h"
#include "backjumping.h"
#include "backtrack.h"
#include "nqueen.h"
#include "forwardchecking.h"

// ./csp 1 5 10 50 50

void solve_queen(int qte, int nb, Couple ***csp)
{
    int *solution;
    for (int i = 0 ; i < qte ; i++)
    {
        printf("Forward checking: \n");
        solution = forwardcheck(nb, nb, -1, csp);
        print_solution(solution, nb);
        if (solution != NULL)
            free(solution);
        printf("-------------------------\n");
        printf("Backjumping:\n");
        solution = timed_backjump(nb, nb, -1, csp);
        print_solution(solution, nb);
        if (solution != NULL)
            free(solution);
        printf("-------------------------\n");
        printf("Backtracking:\n");
        solution = backtrack(nb, nb, -1, csp);
        print_solution(solution, nb);
        if (solution != NULL)
            free(solution);
        printf("=======================\n");
        if (USEDATAFILE)
        {
            FILE *file = fopen(DATAFILE, "a");
            fprintf(file,"\n");
            fclose(file);
        }
    }
}

void solve_random(int qte, int nb_var, int nb_val, int durete, int densite)
{
    Couple ***csp;
    int *solution;
    for (int i = 0 ; i < qte ; i++)
    {
        csp = generate_csp(nb_var, nb_val, densite, durete);
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
        free_csp(nb_var, csp);
        if (USEDATAFILE)
        {
            FILE *file = fopen(DATAFILE, "a");
            fprintf(file,"\n");
            fclose(file);
        }    
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
    solve_queen(qte, n, csp);
    free_csp(n, csp);
}

void menu_random_csp()
{
    int quantite;
    int nb_var; //Nombre de variable
    int nb_val; // Nombre de valeurs
    int densite; //Densité
    int durete; //Dureté
    Couple ***csp;
    printf("Nombre de variable (min 1): ");
    scanf("\n%d", &nb_var);
    nb_var = nb_var > 0 ? nb_var : 1;
    printf("Nombre de valeurs (min 1): ");
    scanf("\n%d", &nb_val);
    nb_val = nb_val > 0 ? nb_val : 1;
    printf("Densité (0 - 100): ");
    scanf("\n%d", &densite);
    densite = densite >= 0 && densite <= 100 ? densite : 50;
    printf("Durete (0 - 100): ");
    scanf("\n%d", &durete);
    durete = durete >= 0 && durete <= 100 ? durete : 50;
    printf("Nombre de problème à générer et résoudre: (min 1)");
    scanf("\n%d", &quantite);
    quantite = quantite > 0 ? quantite : 1;
    solve_random(quantite, nb_var, nb_val, durete, densite);
}

void menuless(int argc, char **argv)
{
    srand(time(NULL));
    int quantite;
    int nb_var; //Nombre de variable
    int nb_val; // Nombre de valeurs
    int densite; //Densité
    int durete; //Dureté
    Couple ***csp;

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
    
    //Pour les N-reines
    csp = generate_queen(nb_var);
    solve_queen(quantite, nb_var, csp);
    free_csp(nb_var, csp);

    //Pour les aléatoires
    //solve_random(quantite, nb_var, nb_val, durete, densite);
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
    //Réinitialise le fichier data.csv si on décide d'activer la sauvegarde dans le fichier
    if (USEDATAFILE)
    {
        FILE *file = fopen(DATAFILE, "w+");
        fprintf(file,"Forwardchecking,backjumping,backtracking\n");
        fclose(file);
    }
    //Permet une execution avec argument (plus rapide pour l'évaluation des temps d'éxecution )
    (argc > 1) ? menuless(argc, argv) : menu();
    return 0;
}