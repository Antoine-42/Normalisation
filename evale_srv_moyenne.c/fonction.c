//Antoine et Yanis 
#include <stdio.h>
#include "evale_srv_moyenne.h"
 
// Lire les 8 valeurs depuis le fichier
int lireValeurs(int tab[]) {
    FILE *f = fopen("fichier_client.txt", "r");
    if (!f) return 0;
 
    int i = 0;
    while (fscanf(f, "%d,", &tab[i]) == 1 && i < TAILLE) {
        i++;
    }
 
    fclose(f);
    return (i == TAILLE);
}
 
// Supprimer un élément à un index donné
void supprimer(int tab[], int *taille, int index) {
    for (int i = index; i < *taille - 1; i++) {
        tab[i] = tab[i + 1];
    }
    (*taille)--;
}
 
// Trouver l’indice du max dans un tableau
int trouverMax(int tab[], int taille) {
    int max = 0;
    for (int i = 1; i < taille; i++) {
        if (tab[i] > tab[max]) {
            max = i;
        }
    }
    return max;
}
 
// Trouver l’indice du min dans un tableau
int trouverMin(int tab[], int taille) {
    int min = 0;
    for (int i = 1; i < taille; i++) {
        if (tab[i] < tab[min]) {
            min = i;
        }
    }
    return min;
}
 
// Supprime 2 max et 2 min, puis copie les 4 restants dans un tableau float
void filtrerEtConvertir(int original[], float resultat[]) {
    int taille = TAILLE;
 
    // On modifie directement le tableau original
    // Supprimer les 2 plus grands
    for (int i = 0; i < 2; i++) {
        int maxIndex = trouverMax(original, taille);
        supprimer(original, &taille, maxIndex);
    }
 
    // Supprimer les 2 plus petits
    for (int i = 0; i < 2; i++) {
        int minIndex = trouverMin(original, taille);
        supprimer(original, &taille, minIndex);
    }
 
    // Copier les 4 restants
    for (int i = 0; i < RESTE; i++) {
        resultat[i] = (float)original[i];
    }
}
 
// Calcul de la moyenne des 4 valeurs
float calculerMoyenne(float tab[]) {
    float somme = 0;
    for (int i = 0; i < RESTE; i++) {
        somme += tab[i];
    }
    return somme / RESTE;
}
 
// Affiche un tableau float
void afficherValeurs(float tab[], int taille) {
    for (int i = 0; i < taille; i++) {
        printf("%.0f ", tab[i]);
    }
    printf("\n");
}
