#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
#define PORT 1618
#define BUFFER_SIZE 1024
 
int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    FILE *fichier;
    size_t bytesRead;
 
    // Création du socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }
 
    // Configuration de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Adresse du serveur (localhost)
 
    // Connexion au serveur
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Erreur de connexion");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }
 
    printf("Connexion au serveur établie.\n");
 
    // Ouverture du fichier à envoyer
    fichier = fopen("fichier_client.txt", "rb");
    if (fichier == NULL) {
        perror("Erreur d'ouverture du fichier");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }
 
    // Envoi du fichier
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, fichier)) > 0) {
        if (send(clientSocket, buffer, bytesRead, 0) < 0) {
            perror("Erreur lors de l'envoi du fichier");
            fclose(fichier);
            close(clientSocket);
            exit(EXIT_FAILURE);
        }
    }
 
    printf("Fichier envoyé avec succès.\n");
 
    // Fermer le fichier
    fclose(fichier);
 
    // Attendre la réponse du serveur
    int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0'; // Assurer la terminaison de la chaîne
        printf("Réponse du serveur : %s\n", buffer);
    }
 
    // Fermeture de la connexion
    close(clientSocket);
 
    return 0;
}