#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "evale_srv_moyenne.h"
#include "connexion.h"
 
#define PORT 1618
#define BUFFER_SIZE 1024
 
int main() {
    int serveurSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
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
 
    // Réception du fichier envoyé par le client
    FILE *fichierRecu = fopen("fichier_recu.txt", "wb");
    if (!fichierRecu) {
        perror("Erreur d'ouverture du fichier");
        close(clientSocket);
        close(serveurSocket);
        exit(EXIT_FAILURE);
    }
 
    int bytesReceived;
    while ((bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytesReceived, fichierRecu);
    }
    printf("Fichier reçu avec succès.\n");
 
    fclose(fichierRecu);
 
    // Analyse du fichier reçu
    float moyenne = analyse();  // L'analyse se fait sur le fichier "fichier_recu.txt"
    printf("Moyenne calculée : %.2f\n", moyenne);
 
    // Envoi de la moyenne au client
    char messageMoyenne[BUFFER_SIZE];
    snprintf(messageMoyenne, sizeof(messageMoyenne), "Moyenne : %.2f", moyenne);
    send(clientSocket, messageMoyenne, strlen(messageMoyenne), 0);
 
    // Fermeture des sockets
    close(clientSocket);
    close(serveurSocket);
 
    return 0;
}