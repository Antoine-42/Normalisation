//Antoine
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

    // Lire les valeurs tant qu'on peut et qu'on n'a pas atteint la limite
    while (fscanf(fichier, "%d", &valeurs[i]) == 1) {
        i++;
        if (i > TAILLE) break; // Plus que 8 ? On sort !
    }

    fclose(fichier);

    // Vérifie qu'on a exactement 8 valeurs
    if (i != TAILLE) {
        printf("Erreur : nombre de valeurs incorrect (il faut exactement %d valeurs).\n", TAILLE);
        return 1;
    }

    // Trouver les deux plus grandes valeurs
    int max1 = valeurs[0], max2 = valeurs[0], i1 = 0, i2 = 0;

    for (i = 1; i < TAILLE; i++) {
        if (valeurs[i] > max1) {
            max2 = max1; i2 = i1;
            max1 = valeurs[i]; i1 = i;
        } else if (valeurs[i] > max2 || i1 == i2) {
            max2 = valeurs[i]; i2 = i;
        }
    }

    // Afficher les valeurs sauf les deux plus grandes
    printf("Valeurs sans les deux plus grandes (%d et %d) :\n", max1, max2);
    for (i = 0; i < TAILLE; i++) {
        if (i != i1 && i != i2) {
            printf("%d ", valeurs[i]);
        }
    }

    printf("\n");
    return 0;
}
