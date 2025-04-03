//yanis
#include <stdio.h>
 
#define TAILLE 8
 
int main() {
    FILE *fichier = fopen("Valeurs.txt", "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return 1;
    }
 
    int valeurs[TAILLE];
    int i = 0;
 
    // Lire les valeurs séparées par des virgules
    while (fscanf(fichier, "%d,", &valeurs[i]) == 1) {
        i++;
        if (i > TAILLE) break;
    }
 
    fclose(fichier);
 
    if (i != TAILLE) {
        printf("Erreur : nombre de valeurs incorrect (il faut exactement %d valeurs).\n", TAILLE);
        return 1;
    }
 
    // Trouver les deux plus petites valeurs
    int min1 = valeurs[0], min2 = valeurs[0];
    int i1 = 0, i2 = 0;
 
    for (i = 1; i < TAILLE; i++) {
        if (valeurs[i] < min1) {
            min2 = min1; i2 = i1;
            min1 = valeurs[i]; i1 = i;
        } else if (valeurs[i] < min2 || i1 == i2) {
            min2 = valeurs[i]; i2 = i;
        }
    }
 
    // Afficher les valeurs sauf les deux plus petites
    printf("Valeurs sans les deux plus petites (%d et %d) :\n", min1, min2);
    for (i = 0; i < TAILLE; i++) {
        if (i != i1 && i != i2) {
            printf("%d ", valeurs[i]);
        }
    }
 
    printf("\n");
    return 0;
}