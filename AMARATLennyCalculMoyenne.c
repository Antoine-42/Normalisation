//Lenny AMARAT Calcule de la moyenne

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Déclaration du tableau de taille 4 pour stocker les valeurs
    float chiffres[4];
    int i;
    float somme = 0.0, moyenne;

    // Ouvrir le fichier "valeur.txt" pour lecture
    FILE *fichier = fopen("valeur.txt", "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier valeur.txt\n");
        return 1;
    }

    // Lire les 4 valeurs depuis le fichier et les stocker dans le tableau
    for (i = 0; i < 4; i++) {
        if (fscanf(fichier, "%f,", &chiffres[i]) != 1) {
            fprintf(stderr, "Erreur lors de la lecture de la valeur %d depuis le fichier\n", i + 1);
            fclose(fichier);
            return 1;
        }
    }

    // Fermer le fichier après la lecture
    fclose(fichier);

    // Calculer la somme des chiffres
    for (i = 0; i < 4; i++) {
        somme += chiffres[i];
    }

    // Calculer la moyenne
    moyenne = somme / 4;

    // Afficher la moyenne
    printf("La moyenne des 4 chiffres est : %.2f\n", moyenne);

    return 0;
}