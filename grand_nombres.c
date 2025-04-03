// antoine
#include <stdio.h>

int main() {
    int a[8];
    int i = 0;

    // Lire les 8 chiffres
    printf("Entrez 8 chiffres :\n");
    while (i < 8) {
        scanf("%d", &a[i]);
        i++;
    }

    // Trouver le plus grand
    int max1 = a[0], i1 = 0;
    i = 1;
    while (i < 8) {
        if (a[i] > max1) {
            max1 = a[i];
            i1 = i;
        }
        i++;
    }

    // Marquer le plus grand
    a[i1] = -1;

    // Trouver le deuxième plus grand
    int max2 = -1, i2 = -1;
    i = 0;
    while (i < 8) {
        if (a[i] > max2) {
            max2 = a[i];
            i2 = i;
        }
        i++;
    }

    // Marquer le deuxième plus grand
    a[i2] = -1;

    // Afficher les chiffres restants
    i = 0;
    while (i < 8) {
        if (a[i] != -1)
            printf("%d ", a[i]);
        i++;
    }

    return 0;
}
