//Lenny AMARAT Calcule de la moyenne

#include <stdio.h>

int main() {
    // Déclaration de la liste avec 4 chiffres
    float chiffres[4] = {100, 258, 654, 558};
    int i;
    float somme = 0.0, moyenne;

    // Calculer la somme des chiffres
    for (i = 0; i < 4; i++) {
        somme += chiffres[i];
    }

    // Calculer la moyenne
    moyenne = somme / 4;

    // Afficher la moyenne
    printf("La moyenne des 4 chiffres restant est : %.2f\n", moyenne);

    return 0;
}