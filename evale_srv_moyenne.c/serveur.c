#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "connexion.h"
#define PORT 1618
#define BUFFER_SIZE 1024
int main() {
    int serveurSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    float moyenne;
    socklen_t addrLen = sizeof(clientAddr);
    // Création du socket
    serveurSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serveurSocket < 0) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }
    // Configuration de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    // Liaison du socket au port
    if (bind(serveurSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Erreur lors de la liaison");
        close(serveurSocket);
        exit(EXIT_FAILURE);
    }
    // Écoute des connexions entrantes
    if (listen(serveurSocket, 5) < 0) {
        perror("Erreur lors de l'écoute");
        close(serveurSocket);
        exit(EXIT_FAILURE);
    }
    printf("Serveur en attente de connexions sur le port %d...\n", PORT);
    // Acceptation d'une connexion client
    clientSocket = accept(serveurSocket, (struct sockaddr *)&clientAddr, &addrLen);
    if (clientSocket < 0) {
        perror("Erreur lors de l'acceptation");
        close(serveurSocket);
        exit(EXIT_FAILURE);
    }
    printf("Client connecté !\n");
    // Réception des données
    int received = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
    if (received > 0) {
        buffer[received] = '\0'; // Assurer la terminaison de la chaîne
        printf("Message reçu : %s\n", buffer);
 
        send(clientSocket, "Message reçu !", strlen("Message reçu !"), 0);
 
        // Appel à la fonction analyse, en supposant qu'elle modifie la variable moyenne
        moyenne = analyse(); // passage par adresse nécessaire pour modifier la variable
 
        // Envoi de la moyenne formatée
        char moyenneMessage[BUFFER_SIZE];
        snprintf(moyenneMessage, sizeof(moyenneMessage), "Moyenne : %.2f", moyenne);
        send(clientSocket, moyenneMessage, strlen(moyenneMessage), 0);
    }
 
    // Fermeture des sockets
    close(clientSocket);
    close(serveurSocket);
    return 0;
}