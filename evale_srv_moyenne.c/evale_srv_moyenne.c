//yanis et antoine
#include <stdio.h>
#include "evale_srv_moyenne.h"

int main() {
    int valeurs[TAILLE];
    float resultat[RESTE];
 
    if (!lireValeurs(valeurs)) {
        printf("Erreur : fichier introuvable ou nombre de valeurs incorrect.\n");
        return 1;
    }
 
    filtrerEtConvertir(valeurs, resultat);
 
    printf("Valeurs conservées après suppression des extrêmes :\n");
    afficherValeurs(resultat, RESTE);
 
    float moyenne = calculerMoyenne(resultat);
    printf("Moyenne : %.2f\n", moyenne);
 
    return 0;
}
